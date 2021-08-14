/******************************************************************************
 *  @file         muggle_cpp.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-08
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        muggle cpp
 *****************************************************************************/

#ifndef MUGGLE_CPP_H_
#define MUGGLE_CPP_H_

// mugglec
#include "muggle/c/muggle_c.h"

// base
#include "muggle/cpp/base/macro.h"

// version
#include "muggle/cpp/version/version.h"

// log
#include "muggle/cpp/log/log.h"

// memory
#include "muggle/cpp/memory/interface_memory_pool.hpp"
#include "muggle/cpp/memory/memory_pool.hpp"
#include "muggle/cpp/memory/threadsafe_memory_pool.hpp"
#include "muggle/cpp/memory/sowr_memory_pool.hpp"

// sync
#include "muggle/cpp/sync/channel.h"
#include "muggle/cpp/sync/ring_buffer.h"

// net
#include "muggle/cpp/net/socket_peer.h"
#include "muggle/cpp/net/socket_handle.h"
#include "muggle/cpp/net/tcp_client.h"
#include "muggle/cpp/net/tcp_server.h"
#include "muggle/cpp/net/udp_client.h"
#include "muggle/cpp/net/udp_server.h"

// os
#include "muggle/cpp/os/dl.h"
#include "muggle/cpp/os/os.h"
#include "muggle/cpp/os/path.h"

#endif /* ifndef MUGGLE_CPP_H_ */
