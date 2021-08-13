/******************************************************************************
 *  @file         udp_client.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-13
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp udp client
 *****************************************************************************/

#ifndef MUGGLE_CPP_UDP_CLIENT_H_
#define MUGGLE_CPP_UDP_CLIENT_H_

#include "muggle/cpp/base/macro.h"
#include "muggle/cpp/net/socket_peer.h"
#include "muggle/cpp/net/socket_handle.h"

NS_MUGGLE_BEGIN

class UdpClient
{
public:
	/**
	 * @brief UDP client constructor
	 */
	MUGGLE_CPP_EXPORT
	UdpClient();

	/**
	 * @brief UDP client destructor
	 */
	MUGGLE_CPP_EXPORT
	virtual ~UdpClient();

	/**
	 * @brief  run udp client event loop
	 */
	MUGGLE_CPP_EXPORT
	void run();

	/**
	 * @brief set udp client handle
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
	 * @brief set timer
	 *
	 * @param ms  timer interval, milli seconds
	 */
	MUGGLE_CPP_EXPORT
	void setTimer(int ms);

	/**
	 * @brief set auto reconnect
	 *
	 * NOTE: for UDP reconnect, only used in connect target in same machine
	 *
	 * @param flag         whether or not auto reconnect
	 * @param interval_ms  reconnect interval time, milli seconds
	 */
	MUGGLE_CPP_EXPORT
	void setAutoReconnect(bool flag, int interval_ms);

	/**
	 * @brief set socket send buffer size
	 *
	 * @param sndbuf_size  send buffer size
	 *
	 * @return boolean value
	 */
	MUGGLE_CPP_EXPORT
	void setSndBuf(int sndbuf_size);

	/**
	 * @brief set socket receive buffer size
	 *
	 * @param rcvbuf_size  receive buffer size
	 *
	 * @return boolean value
	 */
	MUGGLE_CPP_EXPORT
	void setRcvBuf(int rcvbuf_size);

private:
	/**
	 * @brief update socket option
	 */
	MUGGLE_CPP_EXPORT
	void updateSocketOption(muggle_socket_peer_t *peer);

private:
	muggle_socket_peer_t           *connect_peer_;  //!< connected socket peer
	muggle_socket_event_init_arg_t ev_init_arg_;    //!< event init arguments

	std::string host_;                   //!< connect host
	std::string serv_;                   //!< connect serv/port-number
	bool        auto_reconnect_;         //!< auto reconnect
	int         auto_recon_interval_ms_; //!< reconnect interval milli seconds

	int sndbuf_size_;  //!< udp socket send buffer size
	int rcvbuf_size_;  //!< udp socket recv buffer size
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_UDP_CLIENT_H_ */
