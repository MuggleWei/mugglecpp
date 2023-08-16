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
	static uint16_t Swap(uint16_t val);

	MUGGLE_CPP_EXPORT
	static uint32_t Swap(uint32_t val);

	MUGGLE_CPP_EXPORT
	static uint64_t Swap(uint64_t val);

	MUGGLE_CPP_EXPORT
	static int16_t Swap(int16_t val);

	MUGGLE_CPP_EXPORT
	static int32_t Swap(int32_t val);

	MUGGLE_CPP_EXPORT
	static int64_t Swap(int64_t val);

	MUGGLE_CPP_EXPORT
	static float Swap(float val);

	MUGGLE_CPP_EXPORT
	static double Swap(double val);
};

NS_MUGGLE_END

#endif // !MUGGLE_CPP_ENDIAN_H_
