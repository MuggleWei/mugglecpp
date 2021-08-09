/******************************************************************************
 *  @file         pipe.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-09
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp pipe
 *****************************************************************************/

#ifndef MUGGLE_CPP_PIPE_H_
#define MUGGLE_CPP_PIPE_H_

#include "muggle/cpp/base/macro.h"

NS_MUGGLE_BEGIN

class Pipe
{
public:
	/**
	 * @brief push data into pipe
	 *
	 * @param data  data pointer
	 *
	 * @return
	 *     - on success, return 0
	 *     - on failed, return error code in muggle/c/base/err.h
	 */
	MUGGLE_CPP_EXPORT
	virtual int push(void *data) = 0;

	/**
	 * @brief read data from pipe
	 *
	 * @return data pointer
	 */
	MUGGLE_CPP_EXPORT
	virtual void* read() = 0;
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_PIPE_H_ */
