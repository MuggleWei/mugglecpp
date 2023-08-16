/******************************************************************************
 *  @file         endian.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2023-08-16
 *  @copyright    Copyright 2023 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp endian
 *****************************************************************************/

#ifndef MUGGLE_CPP_ENDIAN_H_
#define MUGGLE_CPP_ENDIAN_H_

#include <stdint.h>
#include "muggle/cpp/base/macro.h"

NS_MUGGLE_BEGIN

class Endian {
public:
	MUGGLE_CPP_EXPORT
	static void Swap(uint16_t &val);

	MUGGLE_CPP_EXPORT
	static void Swap(uint32_t &val);

	MUGGLE_CPP_EXPORT
	static void Swap(uint64_t &val);
};

NS_MUGGLE_END

#endif // !MUGGLE_CPP_ENDIAN_H_
