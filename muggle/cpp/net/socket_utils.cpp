#include "socket_utils.h"
#include <stdlib.h>
#include <string.h>
#include "muggle/c/net/socket_utils.h"

NS_MUGGLE_BEGIN

static SocketContext* PackSocketContext(muggle_socket_t fd, int socktype)
{
	muggle_socket_context_t *ctx = (muggle_socket_context_t*)malloc(sizeof(muggle_socket_context_t));
	if (muggle_socket_ctx_init(ctx, fd, NULL, socktype) != 0)
	{
		free(ctx);
		muggle_socket_close(fd);
		return nullptr;
	}

	SocketContext *socket_ctx = new SocketContext(ctx);
	if (socket_ctx == nullptr)
	{
		free(ctx);
		muggle_socket_close(fd);
		return nullptr;
	}

	return socket_ctx;
}

SocketContext* SocketUtils::TCPListen(const char *host, const char *serv, int backlog)
{
	muggle_socket_t fd = muggle_tcp_listen(host, serv, backlog);
	if (fd == MUGGLE_INVALID_SOCKET)
	{
		return nullptr;
	}

	return PackSocketContext(fd, MUGGLE_SOCKET_CTX_TYPE_TCP_LISTEN);
}

SocketContext* SocketUtils::TCPConnect(const char *host, const char *serv, int timeout_sec)
{
	muggle_socket_t fd = muggle_tcp_connect(host, serv, timeout_sec);
	if (fd == MUGGLE_INVALID_SOCKET)
	{
		return nullptr;
	}

	return PackSocketContext(fd, MUGGLE_SOCKET_CTX_TYPE_TCP_CLIENT);
}

SocketContext* SocketUtils::UDPBind(const char *host, const char *serv)
{
	muggle_socket_t fd = muggle_udp_bind(host, serv);
	if (fd == MUGGLE_INVALID_SOCKET)
	{
		return nullptr;
	}

	return PackSocketContext(fd, MUGGLE_SOCKET_CTX_TYPE_UDP);
}

SocketContext* SocketUtils::UDPConnect(const char *host, const char *serv)
{
	muggle_socket_t fd = muggle_udp_connect(host, serv);
	if (fd == MUGGLE_INVALID_SOCKET)
	{
		return nullptr;
	}

	return PackSocketContext(fd, MUGGLE_SOCKET_CTX_TYPE_UDP);
}

SocketContext* SocketUtils::McastJoin(
		const char *host,
		const char *serv,
		const char *iface,
		const char *src_grp)
{
	muggle_socket_t fd = muggle_mcast_join(host, serv, iface, src_grp);
	if (fd == MUGGLE_INVALID_SOCKET)
	{
		return nullptr;
	}

	return PackSocketContext(fd, MUGGLE_SOCKET_CTX_TYPE_UDP);
}

int SocketUtils::McastLeave(
		SocketContext *socket_ctx,
		const char *host,
		const char *serv,
		const char *iface,
		const char *src_grp)
{
	return muggle_mcast_leave(socket_ctx->GetSocket(), host, serv, iface, src_grp);
}

NS_MUGGLE_END
