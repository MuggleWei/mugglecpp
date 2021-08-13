/******************************************************************************
 *  @file         tcp_server.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-13
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp tcp server
 *****************************************************************************/

#ifndef MUGGLE_CPP_TCP_SERVER_H_
#define MUGGLE_CPP_TCP_SERVER_H_

#include <string>
#include "muggle/cpp/base/macro.h"
#include "muggle/cpp/net/socket_peer.h"
#include "muggle/cpp/net/socket_handle.h"

NS_MUGGLE_BEGIN

class TcpServer
{
public:
	/**
	 * @brief tcp server constructor
	 */
	MUGGLE_CPP_EXPORT
	TcpServer();

	/**
	 * @brief tcp server destructor
	 */
	MUGGLE_CPP_EXPORT
	virtual ~TcpServer();

	/**
	 * @brief run tcp server event loop
	 */
	MUGGLE_CPP_EXPORT
	void run();

	/**
	 * @brief set tcp server handle
	 *
	 * @param handle socket handle pointer
	 */
	MUGGLE_CPP_EXPORT
	void setHandle(SocketHandle *handle);

	/**
	 * @brief set listen address
	 *
	 * @param host  listen host
	 * @param serv  listen service name or port
	 */
	MUGGLE_CPP_EXPORT
	void setListenAddr(const char *host, const char *serv);

	/**
	 * @brief set tcp nodelay
	 *
	 * @param flag  true or false
	 */
	MUGGLE_CPP_EXPORT
	void setTcpNoDelay(bool flag);

	/**
	 * @brief set timer
	 *
	 * @param ms  timer interval, milli seconds
	 */
	MUGGLE_CPP_EXPORT
	void setTimer(int ms);

	/**
	 * @brief set hints max peer
	 *
	 * @param hints_max_peer  hints max peer
	 */
	MUGGLE_CPP_EXPORT
	void setHintsMaxPeer(int hints_max_peer);

private:
	muggle_socket_peer_t           *listener_;    //!< listen socket peer
	muggle_socket_event_init_arg_t ev_init_arg_;  //!< event init arguments

	std::string host_;         //!< listen host
	std::string serv_;         //!< listen serv/port-number
	bool        tcp_nodelay_;  //!< tcp nodelay
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_TCP_SERVER_H_ */
