#include "udp_client.h"
#include <string.h>
#include "muggle/c/net/socket_utils.h"
#include "muggle/c/base/sleep.h"
#include "muggle/cpp/log/log.h"

NS_MUGGLE_BEGIN

static void udp_client_on_connect(
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

static void udp_client_on_error(muggle_socket_event_t *ev, muggle_socket_peer_t *peer)
{
	SocketHandle *handle = (SocketHandle*)ev->datas;
	if (handle)
	{
		handle->onError(ev, (SocketPeer*)peer->data);
	}

	// client disconnect and event loop exit
	muggle_socket_event_loop_exit(ev);
}

static void udp_client_on_close(muggle_socket_event_t *ev, muggle_socket_peer_t *peer)
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

static void udp_client_on_message(muggle_socket_event_t *ev, muggle_socket_peer_t *peer)
{
	SocketHandle *handle = (SocketHandle*)ev->datas;
	if (handle)
	{
		handle->onMessage(ev, (SocketPeer*)peer->data);
	}
}

static void udp_client_on_timer(muggle_socket_event_t *ev)
{
	SocketHandle *handle = (SocketHandle*)ev->datas;
	if (handle)
	{
		handle->onTimer(ev);
	}
}

UdpClient::UdpClient()
	: connect_peer_(nullptr)
	, auto_reconnect_(false)
	, auto_recon_interval_ms_(0)
	, sndbuf_size_(0)
	, rcvbuf_size_(0)
{
	memset(&ev_init_arg_, 0, sizeof(ev_init_arg_));
	ev_init_arg_.timeout_ms = -1;
}

UdpClient::~UdpClient()
{}

void UdpClient::run()
{
	while (true)
	{
		muggle_socket_peer_t peer;
		muggle_socket_t ret_fd = muggle_udp_connect(host_.c_str(), serv_.c_str(), &peer);
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

		// set socket option
		updateSocketOption(&peer);

		// fillup event loop input arguments
		ev_init_arg_.cnt_peer = 1;
		ev_init_arg_.peers = &peer;
		ev_init_arg_.p_peers = &connect_peer_;
		ev_init_arg_.hints_max_peer = 2;
		ev_init_arg_.on_connect = udp_client_on_connect;
		ev_init_arg_.on_error = udp_client_on_error;
		ev_init_arg_.on_close = udp_client_on_close;
		ev_init_arg_.on_message = udp_client_on_message;
		ev_init_arg_.on_timer = udp_client_on_timer;

		// event loop init
		muggle_socket_event_t ev;
		if (muggle_socket_event_init(&ev_init_arg_, &ev) != 0)
		{
			LOG_ERROR("failed init socket event");
			exit(EXIT_FAILURE);
		}

		// on client connection
		udp_client_on_connect(&ev, NULL, connect_peer_);

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

void UdpClient::setHandle(SocketHandle *handle)
{
	ev_init_arg_.datas = handle;
}

void UdpClient::setConnectAddr(const char *host, const char *serv)
{
	host_ = host;
	serv_ = serv;
}

void UdpClient::setTimer(int ms)
{
	ev_init_arg_.timeout_ms = ms;
}

void UdpClient::setAutoReconnect(bool flag, int interval_ms)
{
	auto_reconnect_ = flag;
	auto_recon_interval_ms_ = interval_ms;
}

void UdpClient::setSndBuf(int sndbuf_size)
{
	sndbuf_size_ = sndbuf_size;
}

void UdpClient::setRcvBuf(int rcvbuf_size)
{
	rcvbuf_size_ = rcvbuf_size;
}

void UdpClient::updateSocketOption(muggle_socket_peer_t *peer)
{
	if (sndbuf_size_ > 0)
	{
#if MUGGLE_PLATFORM_WINDOWS
		int ret = setsockopt(peer->fd, SOL_SOCKET, SO_SNDBUF, (const char*)&sndbuf_size_, sizeof(sndbuf_size_));
#else
		int ret = setsockopt(peer->fd, SOL_SOCKET, SO_SNDBUF, &sndbuf_size_, sizeof(sndbuf_size_));
#endif
		if (ret != 0)
		{
			char err_msg[1024];
			muggle_socket_strerror(MUGGLE_SOCKET_LAST_ERRNO, err_msg, sizeof(err_msg));
			LOG_WARNING("failed set udp socket send buffer: %s", err_msg);
		}
	}

	if (rcvbuf_size_ > 0)
	{
#if MUGGLE_PLATFORM_WINDOWS
		int ret = setsockopt(peer->fd, SOL_SOCKET, SO_SNDBUF, (const char*)&rcvbuf_size_, sizeof(rcvbuf_size_));
#else
		int ret = setsockopt(peer->fd, SOL_SOCKET, SO_SNDBUF, &rcvbuf_size_, sizeof(rcvbuf_size_));
#endif
		if (ret != 0)
		{
			char err_msg[1024];
			muggle_socket_strerror(MUGGLE_SOCKET_LAST_ERRNO, err_msg, sizeof(err_msg));
			LOG_WARNING("failed set udp socket send buffer: %s", err_msg);
		}
	}
}

NS_MUGGLE_END
