/******************************************************************************
 *  @file         channel.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-09
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp channel
 *****************************************************************************/

#ifndef MUGGLE_CPP_CHANNEL_H_
#define MUGGLE_CPP_CHANNEL_H_

#include "muggle/cpp/base/macro.h"
#include "muggle/c/sync/channel.h"
#include <stdint.h>

NS_MUGGLE_BEGIN

class Channel
{
public:
	/**
	 * @brief channel constructor
	 *
	 * @param capacity  capacity of channel
	 * @param flags     bitwise or of MUGGLE_CHANNEL_FLAG_*
	 */
	MUGGLE_CPP_EXPORT
	Channel(uint32_t capacity, int flags);

	/**
	 * @brief channel destructor
	 */
	MUGGLE_CPP_EXPORT
	virtual ~Channel();

	/**
	 * @brief write data into channel
	 *
	 * @param data  data pointer
	 *
	 * @return
	 *     - on success, return 0
	 *     - on failed, return error code in muggle/c/base/err.h
	 */
	MUGGLE_CPP_EXPORT
	virtual int Write(void *data);

	/**
	 * @brief read data from channel
	 *
	 * @return data pointer
	 */
	MUGGLE_CPP_EXPORT
	virtual void* Read();

private:
	muggle_channel_t channel_;
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_CHANNEL_H_ */
