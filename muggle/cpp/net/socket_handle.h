/******************************************************************************
 *  @file         socket_handle.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-10
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp socket handle
 *****************************************************************************/

#ifndef MUGGLE_CPP_SOCKET_HANDLE_H_
#define MUGGLE_CPP_SOCKET_HANDLE_H_

#include "muggle/c/net/socket_event.h"
#include "muggle/cpp/base/macro.h"
#include "muggle/cpp/net/socket_peer.h"

NS_MUGGLE_BEGIN

class SocketHandle
{
public:
	/**
	 * @brief socket handle constructor
	 */
	MUGGLE_CPP_EXPORT
	SocketHandle();

	/**
	 * @brief socket handle destructor
	 */
	MUGGLE_CPP_EXPORT
	virtual ~SocketHandle();

	/**
	 * @brief socket callback function - on socket success bind addr
	 */
	virtual void onBind(muggle_socket_event_t *ev, SocketPeer *peer);

	/**
	 * @brief socket callback function - on socket success listen addr
	 */
	virtual void onListen(muggle_socket_event_t *ev, SocketPeer *peer);

	/**
	 * @brief socket callback function - onConnect
	 */
	MUGGLE_CPP_EXPORT
	virtual void onConnect(muggle_socket_event_t *ev, SocketPeer *peer);

	/**
	 * @brief socket callback function - onError
	 */
	MUGGLE_CPP_EXPORT
	virtual void onError(muggle_socket_event_t *ev, SocketPeer *peer);

	/**
	 * @brief socket callback function - onMessage
	 */
	MUGGLE_CPP_EXPORT
	virtual void onMessage(muggle_socket_event_t *ev, SocketPeer *peer);

	/**
	 * @brief socket callback function - onTimer
	 */
	MUGGLE_CPP_EXPORT
	virtual void onTimer(muggle_socket_event_t *ev);

	/**
	 * @brief socket callback function - onClose
	 */
	MUGGLE_CPP_EXPORT
	virtual void onClose(muggle_socket_event_t *ev, SocketPeer *peer);
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_SOCKET_HANDLE_H_ */
