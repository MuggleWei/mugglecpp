#include "udp_server.h"
#include <string.h>
#include "muggle/c/net/socket_utils.h"
#include "muggle/c/base/sleep.h"
#include "muggle/cpp/log/log.h"

NS_MUGGLE_BEGIN

static void udp_server_on_close(muggle_socket_event_t *ev, muggle_socket_peer_t *peer)
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

static void udp_server_on_message(muggle_socket_event_t *ev, muggle_socket_peer_t *peer)
{
	SocketHandle *handle = (SocketHandle*)ev->datas;
	if (handle)
	{
		handle->onMessage(ev, (SocketPeer*)peer->data);
	}
}

static void udp_server_on_timer(muggle_socket_event_t *ev)
{
	SocketHandle *handle = (SocketHandle*)ev->datas;
	if (handle)
	{
		handle->onTimer(ev);
	}
}

UdpServer::UdpServer()
	: bind_peer_(nullptr)
	, sndbuf_size_(0)
	, rcvbuf_size_(0)
{
	memset(&ev_init_arg_, 0, sizeof(ev_init_arg_));
	ev_init_arg_.timeout_ms = -1;
}

UdpServer::~UdpServer()
{}

void UdpServer::run()
{
	// create udp bind peer
	muggle_socket_peer_t peer;
	if (muggle_udp_bind(host_.c_str(), serv_.c_str(), &peer) == MUGGLE_INVALID_SOCKET)
	{
		LOG_ERROR("failed create udp bind for %s:%s", host_.c_str(), serv_.c_str());
		return;
	}

	// update socket option
	updateSocketOption(&peer);

	// fillup event loop input arguments
	ev_init_arg_.cnt_peer = 1;
	ev_init_arg_.peers = &peer;
	ev_init_arg_.p_peers = &bind_peer_;
	ev_init_arg_.on_connect = nullptr;
	ev_init_arg_.on_error = nullptr;
	ev_init_arg_.on_close = udp_server_on_close;
	ev_init_arg_.on_message = udp_server_on_message;
	ev_init_arg_.on_timer = udp_server_on_timer;

	// event loop
	muggle_socket_event_t ev;
	if (muggle_socket_event_init(&ev_init_arg_, &ev) != 0)
	{
		MUGGLE_LOG_ERROR("failed init socket event");
		exit(EXIT_FAILURE);
	}

	// bind socket peer
	SocketPeer *socket_peer = new SocketPeer();
	if (socket_peer == nullptr)
	{
		LOG_ERROR("failed allocate memory for socket peer");
		muggle_socket_event_loop_exit(&ev);
		muggle_socket_event_loop(&ev);
		return;
	}
	socket_peer->setPeer(bind_peer_);
	bind_peer_->data = socket_peer;

	muggle_socket_event_loop(&ev);
}

void UdpServer::setHandle(SocketHandle *handle)
{
	ev_init_arg_.datas = handle;
}

void UdpServer::setBindAddr(const char *host, const char *serv)
{
	host_ = host;
	serv_ = serv;
}

void UdpServer::setTimer(int ms)
{
	ev_init_arg_.timeout_ms = ms;
}

void UdpServer::setHintsMaxPeer(int hints_max_peer)
{
	ev_init_arg_.hints_max_peer = hints_max_peer;
}

void UdpServer::setSndBuf(int sndbuf_size)
{
	sndbuf_size_ = sndbuf_size;
}

void UdpServer::setRcvBuf(int rcvbuf_size)
{
	rcvbuf_size_ = rcvbuf_size;
}

void UdpServer::updateSocketOption(muggle_socket_peer_t *peer)
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
