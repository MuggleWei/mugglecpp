/******************************************************************************
 *  @file         ringbuffer.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-09
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp ring buffer
 *****************************************************************************/

#ifndef MUGGLE_CPP_RING_BUFFER_H_
#define MUGGLE_CPP_RING_BUFFER_H_

#include "muggle/c/sync/ring_buffer.h"
#include "muggle/c/base/atomic.h"
#include "muggle/cpp/base/macro.h"
#include "muggle/cpp/sync/pipe.h"
#include <stdint.h>

NS_MUGGLE_BEGIN

class RingBuffer : public Pipe
{
public:
	/**
	 * @brief ring buffer constructor
	 *
	 * @param capacity  initialize capacity for ring buffer
 	 * @param flag      bit OR operationg of MUGGLE_RING_BUFFER_FLAG_*
	 */
	MUGGLE_CPP_EXPORT
	RingBuffer(uint32_t capacity, int flags);

	/**
	 * @brief ring buffer destructor
	 */
	MUGGLE_CPP_EXPORT
	virtual ~RingBuffer();

	/**
	 * @brief push data into ring buffer
	 *
	 * @param data  data pointer
	 *
	 * @return
	 *     - on success, return 0
	 *     - on failed, return error code in muggle/c/base/err.h
	 */
	MUGGLE_CPP_EXPORT
	virtual int push(void *data) override;

	/**
	 * @brief read data from ring buffer
	 *
	 * @return data pointer
	 */
	MUGGLE_CPP_EXPORT
	virtual void* read() override;

private:
	muggle_ring_buffer_t ring_buf_;
	muggle_atomic_int    cursor_;
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_RING_BUFFER_H_ */
