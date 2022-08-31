/******************************************************************************
 *  @file         socket_context.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2022-08-31
 *  @copyright    Copyright 2022 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp socket context
 *****************************************************************************/

#ifndef MUGGLE_CPP_SOCKET_CONTEXT_H_
#define MUGGLE_CPP_SOCKET_CONTEXT_H_

#include "muggle/cpp/base/macro.h"
#include "muggle/c/net/socket_context.h"

NS_MUGGLE_BEGIN

class SocketContext
{
public:
	MUGGLE_CPP_EXPORT
	SocketContext(muggle_socket_context_t *socket_ctx);

	MUGGLE_CPP_EXPORT
	virtual ~SocketContext();

	/**
	 * @brief get socket in context
	 *
	 * @return socket file description
	 */
	MUGGLE_CPP_EXPORT
	muggle_socket_t GetSocket();

	/**
	 * @brief get c socket context
	 *
	 * @return c socket context
	 */
	MUGGLE_CPP_EXPORT
	muggle_socket_context_t* GetContext();

	/**
	 * @brief get scket context type
	 *
	 * @return  socket context type, see MUGGLE_SOCKET_CTX_TYPE_*
	 */
	MUGGLE_CPP_EXPORT
	int GetSocketType();

	/**
	 * @brief set user data
	 *
	 * @param user_data user data
	 */
	MUGGLE_CPP_EXPORT
	void SetUserData(void *user_data);

	/**
	 * @brief get user data
	 *
	 * @return user data
	 */
	MUGGLE_CPP_EXPORT
	void* GetUserData();

	/**
	 * @brief set socket opt
	 *
	 * @param level    socket level
	 * @param optname  option name
	 * @param optval   option val
	 * @param optlen   length of optval
	 *
	 * @return 
	 *     - returns 0 on success
	 *     - on error, MUGGLE_SOCKET_ERROR is returned and MUGGLE_SOCKET_LAST_ERRNO is set
	 */
	MUGGLE_CPP_EXPORT
	int SetSockOpt(int level, int optname, const void *optval, muggle_socklen_t optlen);

	/**
	 * @brief get socket opt
	 *
	 * @param level    socket level
	 * @param optname  option name
	 * @param optval   option val
	 * @param optlen   length of optval
	 *
	 * @return 
	 *     - returns 0 on success
	 *     - on error, MUGGLE_SOCKET_ERROR is returned and MUGGLE_SOCKET_LAST_ERRNO is set
	 */
	MUGGLE_CPP_EXPORT
	int GetSockOpt(int level, int optname, void *optval, muggle_socklen_t *optlen);

	/**
	 * @brief set socket block or non-block
	 *
	 * @param on  if 0, set block, otherwise set non block
	 *
	 * @return 
	 *     - returns 0 on success
	 *     - on error, MUGGLE_SOCKET_ERROR is returned and MUGGLE_SOCKET_LAST_ERRNO is set
	 */
	MUGGLE_CPP_EXPORT
	int SetNonBlock(int on);

	/**
	 * @brief mark as wait to close
	 */
	MUGGLE_CPP_EXPORT
	void SetFlagClose();

	/**
	 * @brief reference count retain
	 *
	 * @return
	 *     - on success, return reference count of context after this call
	 *     - on failed, return -1.
	 *     - when reference count already 0, then try to release will return -1
	 */
	MUGGLE_CPP_EXPORT
	int RefCntRetain();

	/**
	 * @brief reference count release
	 *
	 * @return
	 *     - on success, return reference count of context after this call
	 *     - on failed, return -1.
	 *     - when reference count already 0, then try to release will return -1
	 */
	MUGGLE_CPP_EXPORT
	int RefCntRelease();

	/**
	 * @brief shutdown socket in context
	 *
	 * @return
	 *     - returns 0 on success
	 *     - on error, MUGGLE_EVENT_ERROR is returned and MUGGLE_EVENT_LAST_ERRNO is set
	 */
	MUGGLE_CPP_EXPORT
	int Shutdown();

	/**
	 * @brief close socket in context
	 *
	 * @return
	 *     - returns 0 on success
	 *     - on error, MUGGLE_EVENT_ERROR is returned and MUGGLE_EVENT_LAST_ERRNO is set
	 */
	MUGGLE_CPP_EXPORT
	int Close();

	/**
	 * @brief read/recv/recvfrom bytes from socket context
	 *
	 * @param buf      buffer store received bytes
	 * @param len      buffer size
	 * @param flags    recv flags
	 * @param addr     socket address
	 * @param addrlen  socket address length
	 *
	 * @return 
	 *     - on success, thre number of bytes read is returned, 0 indicates end of event context
	 *     - on error, MUGGLE_EVENT_ERROR is returned and MUGGLE_EVENT_LAST_ERRNO is set
	 */
	MUGGLE_CPP_EXPORT
	int Read(void *buf, size_t len);

	MUGGLE_CPP_EXPORT
	int Recv(void *buf, size_t len, int flags);

	MUGGLE_CPP_EXPORT
	int RecvFrom(void *buf, size_t len, int flags, struct sockaddr *addr, muggle_socklen_t *addrlen);

	/**
	 * @brief write len bytes from buffer to event context
	 *
	 * @param buf        buffer store the bytes that need to send
	 * @param len        number of bytes be written
	 * @param flags      send flags
	 * @param dest_addr  dest socket address
	 * @param addrlen    dest socket address length
	 *
	 * @return 
	 *     - on success, thre number of bytes sent is returned, 0 indicates end of event context
	 *     - on error, MUGGLE_EVENT_ERROR is returned and MUGGLE_EVENT_LAST_ERRNO is set
	 */
	MUGGLE_CPP_EXPORT
	int Write(void *buf, size_t len);

	MUGGLE_CPP_EXPORT
	int Send(void *buf, size_t len, int flags);

	MUGGLE_CPP_EXPORT
	int SendTo(void *buf, size_t len, int flags, struct sockaddr *addr, muggle_socklen_t addrlen);

private:
	muggle_socket_context_t *ctx_;

	void *user_data_;
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_SOCKET_CONTEXT_H_ */
