#include "tcp_client.h"
#include <string.h>
#include "muggle/c/base/sleep.h"
#include "muggle/cpp/log/log.h"

NS_MUGGLE_BEGIN

static void tcp_client_on_connect(
	muggle_socket_event_t *ev,
	muggle_socket_peer_t *,
	muggle_socket_peer_t *peer)
{
	SocketPeer *socket_peer = new SocketPeer();
	if (socket_peer == nullptr)
	{
		muggle_socket_peer_close(peer);
		LOG_ERROR("failed allocate memory for socket peer");
		return;
	}

	socket_peer->setPeer(peer);
	peer->data = socket_peer;

	SocketHandle *handle = (SocketHandle*)ev->datas;
	if (handle)
	{
		handle->onConnect(ev, socket_peer);
	}
}

static void tcp_client_on_error(muggle_socket_event_t *ev, muggle_socket_peer_t *peer)
{
	SocketHandle *handle = (SocketHandle*)ev->datas;
	if (handle)
	{
		handle->onError(ev, (SocketPeer*)peer->data);
	}

	// client disconnect and event loop exit
	muggle_socket_event_loop_exit(ev);
}

static void tcp_client_on_close(muggle_socket_event_t *ev, muggle_socket_peer_t *peer)
{
	SocketHandle *handle = (SocketHandle*)ev->datas;
	if (handle)
	{
		handle->onClose(ev, (SocketPeer*)peer->data);
	}

	SocketPeer *socket_peer = (SocketPeer*)peer->data;
	if (socket_peer)
	{
		delete socket_peer;
	}
	peer->data = nullptr;
}

static void tcp_client_on_message(muggle_socket_event_t *ev, muggle_socket_peer_t *peer)
{
	SocketHandle *handle = (SocketHandle*)ev->datas;
	if (handle)
	{
		handle->onMessage(ev, (SocketPeer*)peer->data);
	}
}

static void tcp_client_on_timer(muggle_socket_event_t *ev)
{
	SocketHandle *handle = (SocketHandle*)ev->datas;
	if (handle)
	{
		handle->onTimer(ev);
	}
}

TcpClient::TcpClient()
	: connect_peer_(nullptr)
	, tcp_nodelay_(false)
	, auto_reconnect_(false)
	, auto_recon_interval_ms_(0)
	, conn_timeout_sec_(3)
{
	memset(&ev_init_arg_, 0, sizeof(ev_init_arg_));
}

TcpClient::~TcpClient()
{
}

void TcpClient::run()
{
	while (true)
	{
		muggle_socket_peer_t peer;
		muggle_socket_t ret_fd = muggle_tcp_connect(host_.c_str(), serv_.c_str(), conn_timeout_sec_, &peer);
		if (ret_fd == MUGGLE_INVALID_SOCKET)
		{
			if (auto_reconnect_)
			{
				muggle_msleep(auto_recon_interval_ms_);
				continue;
			}
			else
			{
				break;
			}
		}

		// tcp socket option
		if (tcp_nodelay_)
		{
			int optval = 1;
			setsockopt(peer.fd, IPPROTO_TCP, TCP_NODELAY, (void*)&optval, sizeof(optval));
		}

		// fillup event loop input arguments
		ev_init_arg_.cnt_peer = 1;
		ev_init_arg_.peers = &peer;
		ev_init_arg_.p_peers = &connect_peer_;
		ev_init_arg_.on_connect = tcp_client_on_connect;
		ev_init_arg_.on_error = tcp_client_on_error;
		ev_init_arg_.on_close = tcp_client_on_close;
		ev_init_arg_.on_message = tcp_client_on_message;
		ev_init_arg_.on_timer = tcp_client_on_timer;

		// event loop init
		muggle_socket_event_t ev;
		if (muggle_socket_event_init(&ev_init_arg_, &ev) != 0)
		{
			LOG_ERROR("failed init socket event");
			exit(EXIT_FAILURE);
		}

		// on client connection
		tcp_client_on_connect(&ev, NULL, connect_peer_);

		// event loop
		muggle_socket_event_loop(&ev);

		if (auto_reconnect_)
		{
			muggle_msleep(auto_recon_interval_ms_);
			continue;
		}
		else
		{
			break;
		}
	}
}

void TcpClient::setHandle(SocketHandle *handle)
{
	ev_init_arg_.datas = handle;
}
void TcpClient::setConnectAddr(const char *host, const char *serv)
{
	host_ = host;
	serv_ = serv;
}
void TcpClient::setTcpNoDelay(bool flag)
{
	tcp_nodelay_ = flag;
}
void TcpClient::setTimer(int ms)
{
	ev_init_arg_.timeout_ms = ms;
}
void TcpClient::setAutoReconnect(bool flag, int interval_ms)
{
	auto_reconnect_ = flag;
	auto_recon_interval_ms_ = interval_ms;
}
void TcpClient::setConnectTimeout(int sec)
{
	conn_timeout_sec_ = sec;
}

NS_MUGGLE_END
