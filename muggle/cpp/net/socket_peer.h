/******************************************************************************
 *  @file         socket_peer.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-10
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp socket peer
 *****************************************************************************/

#ifndef MUGGLE_CPP_SOCKET_PEER_H_
#define MUGGLE_CPP_SOCKET_PEER_H_

#include <string>
#include "muggle/c/net/socket_peer.h"
#include "muggle/cpp/base/macro.h"

NS_MUGGLE_BEGIN

class SocketPeer
{
public:
	/**
	 * @brief socket peer constructor
	 */
	MUGGLE_CPP_EXPORT
	SocketPeer();

	/**
	 * @brief socket peer destructor
	 */
	MUGGLE_CPP_EXPORT
	virtual ~SocketPeer();

	/**
	 * @brief socket peer setter
	 */
	MUGGLE_CPP_EXPORT
	void setPeer(muggle_socket_peer_t *peer);

	/**
	 * @brief socket peer getter
	 */
	MUGGLE_CPP_EXPORT
	muggle_socket_peer_t* getPeer();

	/**
	 * @brief user data setter
	 */
	MUGGLE_CPP_EXPORT
	void setUserData(void *data);

	/**
	 * @brief user data getter
	 */
	MUGGLE_CPP_EXPORT
	void* getUserData();

	/**
	 * @brief increases reference count of socket peer
	 *
	 * @return reference count of peer after this call
	 */
	MUGGLE_CPP_EXPORT
	int retain();

	/**
	 * @brief decreases reference count of socket peer
	 *
	 * @return reference count of peer after this call
	 */
	MUGGLE_CPP_EXPORT
	int release();

	/**
	 * @brief try to close socket peer
	 */
	MUGGLE_CPP_EXPORT
	void close();

	/**
	 * @brief receive messages from a socket peer
	 *
	 * @param buf    buffer store received bytes
	 * @param len    buffer size
	 * @param flags  recv flags
	 *
	 * @return the number of bytes received
	 */
	MUGGLE_CPP_EXPORT
	int recv(void *buf, size_t len, int flags);

	/**
	 * @brief receive messages from a socket peer
	 *
	 * @param buf    buffer store received bytes
	 * @param len    buffer size
	 * @param flags  recv flags
	 * @param addr     socket address
	 * @param addrlen  socket address length
	 *
	 * @return the number of bytes received
	 */
	MUGGLE_CPP_EXPORT
	int recvFrom(
		void *buf, size_t len, int flags,
		struct sockaddr *addr, muggle_socklen_t *addrlen);

	/**
	 * @brief socket send message
	 *
	 * @param buf        buffer store the bytes that need to sent
	 * @param len        buffer size
	 * @param flags      flag
	 *
	 * @return 
	 */
	MUGGLE_CPP_EXPORT
	int send(const void *buf, size_t len, int flags);

	/**
	 * @brief socket send message to dst addr
	 *
	 * @param buf        buffer store the bytes that need to sent
	 * @param len        buffer size
	 * @param flags      flag
	 * @param dest_addr  dest socket address
	 * @param addrlen    dest socket address length
	 *
	 * @return 
	 */
	MUGGLE_CPP_EXPORT
	int sendTo(
		const void *buf, size_t len, int flags,
		const struct sockaddr *dst_addr, muggle_socklen_t addrlen);

	/**
	 * @brief set socket send buffer size
	 *
	 * @param sndbuf_size  send buffer size
	 *
	 * @return boolean value
	 */
	MUGGLE_CPP_EXPORT
	bool setSndBuf(int sndbuf_size);

	/**
	 * @brief set socket receive buffer size
	 *
	 * @param rcvbuf_size  receive buffer size
	 *
	 * @return boolean value
	 */
	MUGGLE_CPP_EXPORT
	bool setRcvBuf(int rcvbuf_size);

private:
	muggle_socket_peer_t *peer_;
	void                 *user_data_;
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_SOCKET_PEER_H_ */
