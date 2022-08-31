#include "socket_context.h"
#include <stdexcept>
#include <string.h>
#include <stdlib.h>

NS_MUGGLE_BEGIN

SocketContext::SocketContext(muggle_socket_context_t *socket_ctx)
	: ctx_(socket_ctx)
	, user_data_(nullptr)
{
	muggle_socket_ctx_set_data(ctx_, this);
}

SocketContext::~SocketContext()
{}

muggle_socket_t SocketContext::GetSocket()
{
	return ctx_->base.fd;
}

muggle_socket_context_t* SocketContext::GetContext()
{
	return ctx_;
}

int SocketContext::GetSocketType()
{
	return muggle_socket_ctx_type(ctx_);
}

void SocketContext::SetUserData(void *user_data)
{
	user_data_ = user_data;
}

void* SocketContext::GetUserData()
{
	return user_data_;
}

int SocketContext::SetSockOpt(int level, int optname, const void *optval, muggle_socklen_t optlen)
{
	muggle_socket_t fd = this->GetSocket();
	return muggle_setsockopt(fd, level, optname, optval, optlen);
}

int SocketContext::GetSockOpt(int level, int optname, void *optval, muggle_socklen_t *optlen)
{
	muggle_socket_t fd = this->GetSocket();
	return muggle_getsockopt(fd, level, optname, optval, optlen);
}

int SocketContext::SetNonBlock(int on)
{
	muggle_socket_t fd = this->GetSocket();
	return muggle_socket_set_nonblock(fd, on);
}

void SocketContext::SetFlagClose()
{
	muggle_socket_ctx_set_flag(ctx_, MUGGLE_EV_CTX_FLAG_CLOSED);
}

void SocketContext::ClearFlags()
{
	ctx_->base.flags = 0;
}

int SocketContext::RefCntRetain()
{
	return muggle_socket_ctx_ref_retain(ctx_);
}

int SocketContext::RefCntRelease()
{
	return muggle_socket_ctx_ref_release(ctx_);
}

int SocketContext::Shutdown()
{
	return muggle_socket_ctx_shutdown(ctx_);
}

int SocketContext::Close()
{
	return muggle_socket_ctx_close(ctx_);
}

int SocketContext::Read(void *buf, size_t len)
{
	return muggle_socket_ctx_read(ctx_, buf, len);
}

int SocketContext::Recv(void *buf, size_t len, int flags)
{
	return muggle_socket_ctx_recv(ctx_, buf, len, flags);
}

int SocketContext::RecvFrom(void *buf, size_t len, int flags, struct sockaddr *addr, muggle_socklen_t *addrlen)
{
	return muggle_socket_ctx_recvfrom(ctx_, buf, len, flags, addr, addrlen);
}

int SocketContext::Write(void *buf, size_t len)
{
	return muggle_socket_ctx_write(ctx_, buf, len);
}

int SocketContext::Send(void *buf, size_t len, int flags)
{
	return muggle_socket_ctx_send(ctx_, buf, len, flags);
}

int SocketContext::SendTo(void *buf, size_t len, int flags, struct sockaddr *addr, muggle_socklen_t addrlen)
{
	return muggle_socket_ctx_sendto(ctx_, buf, len, flags, addr, addrlen);
}


NS_MUGGLE_END
