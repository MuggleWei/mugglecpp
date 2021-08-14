#include "socket_peer.h"
#include <string.h>

NS_MUGGLE_BEGIN

SocketPeer::SocketPeer()
	: peer_(nullptr)
	, user_data_(nullptr)
{
}
SocketPeer::~SocketPeer()
{}

void SocketPeer::setPeer(muggle_socket_peer_t *peer)
{
	peer_ = peer;
}
muggle_socket_peer_t* SocketPeer::getPeer()
{
	return peer_;
}

void SocketPeer::setUserData(void *data)
{
	user_data_ = data;
}
void* SocketPeer::getUserData()
{
	return user_data_;
}

int SocketPeer::retain()
{
	return muggle_socket_peer_retain(peer_);
}
int SocketPeer::release()
{
	return muggle_socket_peer_release(peer_);
}
void SocketPeer::close()
{
	muggle_socket_peer_close(peer_);
}

int SocketPeer::recv(void *buf, size_t len, int flags)
{
	return muggle_socket_peer_recv(peer_, buf, len, flags);
}
int SocketPeer::recvFrom(
	void *buf, size_t len, int flags,
	struct sockaddr *addr, muggle_socklen_t *addrlen)
{
	return muggle_socket_peer_recvfrom(peer_, buf, len, flags, addr, addrlen);
}

int SocketPeer::send(const void *buf, size_t len, int flags)
{
	return muggle_socket_peer_send(peer_, buf, len, flags);
}
int SocketPeer::sendTo(
	const void *buf, size_t len, int flags,
	const struct sockaddr *dst_addr, muggle_socklen_t addrlen)
{
	return muggle_socket_peer_sendto(peer_, buf, len, flags, dst_addr, addrlen);
}

bool SocketPeer::setSndBuf(int sndbuf_size)
{
	if (peer_ && peer_->fd != MUGGLE_INVALID_SOCKET)
	{
		int ret = muggle_setsockopt(peer_->fd, SOL_SOCKET, SO_SNDBUF, (void*)&sndbuf_size, sizeof(sndbuf_size));
		return ret == 0;
	}

	return false;
}
bool SocketPeer::setRcvBuf(int rcvbuf_size)
{
	if (peer_ && peer_->fd != MUGGLE_INVALID_SOCKET)
	{
		int ret = muggle_setsockopt(peer_->fd, SOL_SOCKET, SO_RCVBUF, (void*)&rcvbuf_size, sizeof(rcvbuf_size));
		return ret == 0;
	}

	return false;
}

NS_MUGGLE_END
