/******************************************************************************
 *  @file         net_event_loop.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2022-08-31
 *  @copyright    Copyright 2022 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp network event loop
 *****************************************************************************/

#ifndef MUGGLE_CPP_NET_EVENT_LOOP_H_
#define MUGGLE_CPP_NET_EVENT_LOOP_H_

#include <functional>

#include "muggle/cpp/base/macro.h"
#include "muggle/c/event/event_loop.h"
#include "muggle/c/net/socket_evloop_handle.h"
#include "muggle/cpp/net/socket_context.h"
#include "muggle/cpp/net/net_event_handle.h"

NS_MUGGLE_BEGIN

class NetEventLoop
{
public:
	MUGGLE_CPP_EXPORT
	NetEventLoop(int hints_max_fd, bool use_mem_pool);

	MUGGLE_CPP_EXPORT
	virtual ~NetEventLoop();

	MUGGLE_CPP_EXPORT
	void SetHandle(NetEventHandle *handle);

	MUGGLE_CPP_EXPORT
	NetEventHandle* GetHandle();

	MUGGLE_CPP_EXPORT
	void SetUserData(void *user_data);

	MUGGLE_CPP_EXPORT
	void* GetUserData();

	MUGGLE_CPP_EXPORT
	void AddContext(SocketContext *socket_ctx);

	MUGGLE_CPP_EXPORT
	void Run();

	MUGGLE_CPP_EXPORT
	void Exit();

	/**
	 * @brief set timer interval in milliseconds
	 *
	 * @param ms  milliseconds
	 */
	MUGGLE_CPP_EXPORT
	void SetTimerInterval(int ms);

private:
	muggle_event_loop_t *evloop_;
	muggle_socket_evloop_handle_t *handle_;

	NetEventHandle *net_event_handle_;

	void *user_data_;
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_NET_EVENT_LOOP_H_ */
