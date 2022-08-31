/******************************************************************************
 *  @file         socket_utils.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2022-08-31
 *  @copyright    Copyright 2022 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp socket utils
 *****************************************************************************/

#ifndef MUGGLE_CPP_SOCKET_UTILS_H_
#define MUGGLE_CPP_SOCKET_UTILS_H_

#include "muggle/cpp/base/macro.h"
#include "muggle/cpp/net/socket_context.h"

NS_MUGGLE_BEGIN

class SocketUtils
{
public:
	MUGGLE_CPP_EXPORT
	static SocketContext* TCPListen(const char *host, const char *serv, int backlog);

	MUGGLE_CPP_EXPORT
	static SocketContext* TCPConnect(const char *host, const char *serv, int timeout_sec);

	MUGGLE_CPP_EXPORT
	static SocketContext* UDPBind(const char *host, const char *serv);

	MUGGLE_CPP_EXPORT
	static SocketContext* UDPConnect(const char *host, const char *serv);

	MUGGLE_CPP_EXPORT
	static SocketContext* McastJoin(
		const char *host,
		const char *serv,
		const char *iface,
		const char *src_grp);

	MUGGLE_CPP_EXPORT
	static int McastLeave(
		SocketContext *ctx,
		const char *host,
		const char *serv,
		const char *iface,
		const char *src_grp);
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_SOCKET_UTILS_H_ */
