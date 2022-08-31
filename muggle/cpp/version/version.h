/******************************************************************************
 *  @file         version.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-08
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp version
 *****************************************************************************/

#ifndef MUGGLE_CPP_VERSION_H_
#define MUGGLE_CPP_VERSION_H_

#include "muggle/cpp/base/macro.h"

NS_MUGGLE_BEGIN

/**
 * @brief get mugglecpp version
 *
 * @return mugglecpp version
 */
MUGGLE_CPP_EXPORT
const char* mugglecpp_version();

/**
 * @brief get mugglecpp compile time
 *
 * @return mugglecpp compile time
 */
MUGGLE_CPP_EXPORT
const char* mugglecpp_compile_time();

/**
 * @brief get mugglecpp compile datetime in format yyyy-mm-ddTHH:MM:SS
 *
 * @param buf      buffer for store datetime string, at least 21 bytes in size
 * @param bufsize  size of buffer
 *
 * @return
 *     on success, return buf that store mugglec compile datetime string
 *     on failed, return NULL
 */
MUGGLE_CPP_EXPORT
const char* mugglecpp_compile_time_iso8601(char *buf, int bufsize);

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_VERSION_H_ */
