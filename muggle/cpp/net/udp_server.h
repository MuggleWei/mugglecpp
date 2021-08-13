/******************************************************************************
 *  @file         udp_server.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-13
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp udp server
 *****************************************************************************/

#ifndef MUGGLE_CPP_UDP_SERVER_H_
#define MUGGLE_CPP_UDP_SERVER_H_

#include "muggle/cpp/base/macro.h"
#include "muggle/cpp/net/socket_peer.h"
#include "muggle/cpp/net/socket_handle.h"

NS_MUGGLE_BEGIN

class UdpServer
{
public:
	/**
	 * @brief udp server constructor
	 */
	MUGGLE_CPP_EXPORT
	UdpServer();

	/**
	 * @brief udp server destructor
	 */
	MUGGLE_CPP_EXPORT
	virtual ~UdpServer();

	/**
	 * @brief run udp server event loop
	 */
	MUGGLE_CPP_EXPORT
	void run();

	/**
	 * @brief set udp server handle
	 *
	 * @param handle socket handle pointer
	 */
	MUGGLE_CPP_EXPORT
	void setHandle(SocketHandle *handle);

	/**
	 * @brief set bind address
	 *
	 * @param host  bind host
	 * @param serv  bind service name or port
	 */
	MUGGLE_CPP_EXPORT
	void setBindAddr(const char *host, const char *serv);

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
	muggle_socket_peer_t           *bind_peer_;  //!< bind socket peer
	muggle_socket_event_init_arg_t ev_init_arg_; //!< event init arguments

	std::string host_;                   //!< connect host
	std::string serv_;                   //!< connect serv/port-number

	int sndbuf_size_;  //!< udp socket send buffer size
	int rcvbuf_size_;  //!< udp socket recv buffer size
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_UDP_SERVER_H_ */
