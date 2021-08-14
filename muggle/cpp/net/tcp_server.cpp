#include "tcp_server.h"
#include <string.h>
#include "muggle/cpp/log/log.h"

NS_MUGGLE_BEGIN

static void tcp_server_on_connect(
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

static void tcp_server_on_error(muggle_socket_event_t *ev, muggle_socket_peer_t *peer)
{
	SocketHandle *handle = (SocketHandle*)ev->datas;
	if (handle)
	{
		handle->onError(ev, (SocketPeer*)peer->data);
	}
}

static void tcp_server_on_close(muggle_socket_event_t *ev, muggle_socket_peer_t *peer)
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

static void tcp_server_on_message(muggle_socket_event_t *ev, muggle_socket_peer_t *peer)
{
	SocketHandle *handle = (SocketHandle*)ev->datas;
	if (handle)
	{
		handle->onMessage(ev, (SocketPeer*)peer->data);
	}
}

static void tcp_server_on_timer(muggle_socket_event_t *ev)
{
	SocketHandle *handle = (SocketHandle*)ev->datas;
	if (handle)
	{
		handle->onTimer(ev);
	}
}

TcpServer::TcpServer()
	: listener_(nullptr)
	, tcp_nodelay_(false)
{
	memset(&ev_init_arg_, 0, sizeof(ev_init_arg_));
	ev_init_arg_.timeout_ms = -1;
}

TcpServer::~TcpServer()
{}

void TcpServer::run()
{
	// create tcp listen peer
	muggle_socket_peer_t peer;
	if (muggle_tcp_listen(host_.c_str(), serv_.c_str(), 512, &peer) == MUGGLE_INVALID_SOCKET)
	{
		LOG_ERROR("failed create tcp listen for %s:%s", host_.c_str(), serv_.c_str());
		return;
	}
	getsockname(peer.fd, (struct sockaddr*)&peer.addr, &peer.addr_len);

	// tcp socket option
	if (tcp_nodelay_)
	{
		int optval = 1;
		muggle_setsockopt(peer.fd, IPPROTO_TCP, TCP_NODELAY, (void*)&optval, sizeof(optval));
	}

	// fillup event loop input arguments
	ev_init_arg_.cnt_peer = 1;
	ev_init_arg_.peers = &peer;
	ev_init_arg_.p_peers = &listener_;
	ev_init_arg_.on_connect = tcp_server_on_connect;
	ev_init_arg_.on_error = tcp_server_on_error;
	ev_init_arg_.on_close = tcp_server_on_close;
	ev_init_arg_.on_message = tcp_server_on_message;
	ev_init_arg_.on_timer = tcp_server_on_timer;

	// event loop
	muggle_socket_event_t ev;
	if (muggle_socket_event_init(&ev_init_arg_, &ev) != 0)
	{
		MUGGLE_LOG_ERROR("failed init socket event");
		exit(EXIT_FAILURE);
	}

	// notify success listen
	SocketPeer listener;
	listener.setPeer(listener_);
	listener_->data = &listener;
	if (ev_init_arg_.datas)
	{
		SocketHandle *handle = (SocketHandle*)ev_init_arg_.datas;
		handle->onListen(&ev, &listener);
	}

	muggle_socket_event_loop(&ev);
}

void TcpServer::setHandle(SocketHandle *handle)
{
	ev_init_arg_.datas = handle;
}

void TcpServer::setListenAddr(const char *host, const char *serv)
{
	host_ = host;
	serv_ = serv;
}

void TcpServer::setTcpNoDelay(bool flag)
{
	tcp_nodelay_ = flag;
}

void TcpServer::setTimer(int ms)
{
	ev_init_arg_.timeout_ms = ms;
}

void TcpServer::setHintsMaxPeer(int hints_max_peer)
{
	ev_init_arg_.hints_max_peer = hints_max_peer;
}

NS_MUGGLE_END
