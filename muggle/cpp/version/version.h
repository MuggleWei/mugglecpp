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

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_VERSION_H_ */
