/******************************************************************************
 *  @file         net_event_handle.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2022-08-31
 *  @copyright    Copyright 2022 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp network event handle
 *****************************************************************************/

#ifndef MUGGLE_CPP_NET_EVENT_HANDLE_H_
#define MUGGLE_CPP_NET_EVENT_HANDLE_H_

#include "muggle/cpp/base/macro.h"

NS_MUGGLE_BEGIN

class NetEventLoop;
class SocketContext;

class NetEventHandle
{
public:
	MUGGLE_CPP_EXPORT
	NetEventHandle();

	MUGGLE_CPP_EXPORT
	virtual ~NetEventHandle();

	MUGGLE_CPP_EXPORT
	virtual void OnAddCtx(NetEventLoop *evloop, SocketContext *ctx);

	MUGGLE_CPP_EXPORT
	virtual void OnConnect(NetEventLoop *evloop, SocketContext *ctx);

	MUGGLE_CPP_EXPORT
	virtual void OnMessage(NetEventLoop *evloop, SocketContext *ctx);

	MUGGLE_CPP_EXPORT
	virtual void OnClose(NetEventLoop *evloop, SocketContext *ctx);

	MUGGLE_CPP_EXPORT
	virtual void OnRelease(NetEventLoop *evloop, SocketContext *ctx);

	MUGGLE_CPP_EXPORT
	virtual void OnTimer(NetEventLoop *evloop);
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_NET_EVENT_HANDLE_H_ */
