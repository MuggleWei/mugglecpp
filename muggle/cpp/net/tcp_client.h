/******************************************************************************
 *  @file         tcp_client.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-10
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp tcp client
 *****************************************************************************/

#ifndef MUGGLE_CPP_TCP_CLIENT_H_
#define MUGGLE_CPP_TCP_CLIENT_H_

#include <string>
#include "muggle/cpp/base/macro.h"
#include "muggle/cpp/net/socket_peer.h"
#include "muggle/cpp/net/socket_handle.h"

NS_MUGGLE_BEGIN

class TcpClient
{
public:

	/**
	 * @brief tcp client constructor
	 */
	MUGGLE_CPP_EXPORT
	TcpClient();

	/**
	 * @brief tcp client destructor
	 */
	MUGGLE_CPP_EXPORT
	virtual ~TcpClient();

	/**
	 * @brief run tcp client event loop
	 */
	MUGGLE_CPP_EXPORT
	void run();

	/**
	 * @brief set tcp client handle
	 *
	 * @param handle socket handle pointer
	 */
	MUGGLE_CPP_EXPORT
	void setHandle(SocketHandle *handle);

	/**
	 * @brief set connect address
	 *
	 * @param host  dst host
	 * @param serv  dst service name or port
	 */
	MUGGLE_CPP_EXPORT
	void setConnectAddr(const char *host, const char *serv);

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
	 * @brief set auto reconnect
	 *
	 * @param flag         whether or not auto reconnect
	 * @param interval_ms  reconnect interval time, milli seconds
	 */
	MUGGLE_CPP_EXPORT
	void setAutoReconnect(bool flag, int interval_ms);

	/**
	 * @brief set socket connect timeout
	 *
	 * @param sec  connect timeout, seconds
	 */
	MUGGLE_CPP_EXPORT
	void setConnectTimeout(int sec);

private:
	muggle_socket_peer_t           *connect_peer_;  //!< connected socket peer
	muggle_socket_event_init_arg_t ev_init_arg_;    //!< event init arguments

	std::string host_;                   //!< connect host
	std::string serv_;                   //!< connect serv/port-number
	bool        tcp_nodelay_;            //!< tcp nodelay
	bool        auto_reconnect_;         //!< auto reconnect
	int         auto_recon_interval_ms_; //!< reconnect interval milli seconds
	int         conn_timeout_sec_;       //!< connect timeout seconds
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_TCP_CLIENT_H_ */

