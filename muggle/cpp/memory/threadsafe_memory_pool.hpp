/******************************************************************************
 *  @file         threadsafe_memory_pool.hpp
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-08
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp threadsafe memory pool
 *****************************************************************************/

#ifndef MUGGLE_CPP_THREADSAFE_MEMORY_POOL_H_
#define MUGGLE_CPP_THREADSAFE_MEMORY_POOL_H_

#include <stdexcept>
#include <utility>

#include "muggle/c/memory/threadsafe_memory_pool.h"
#include "muggle/cpp/base/macro.h"
#include "muggle/cpp/memory/interface_memory_pool.hpp"

NS_MUGGLE_BEGIN

/**
 * @brief  mugglecpp threadsafe memory pool
 */
template<typename T>
class ThreadSafeMemoryPool : public IMemoryPool<T>
{
public:
	/**
	 * @brief memory pool constructor
	 *
	 * @param capacity   intialize capacity of memory pool
	 * @param const_cap  use constant capacity
	 */
	ThreadSafeMemoryPool(muggle_atomic_int capacity)
	{
		if (muggle_ts_memory_pool_init(&pool_, capacity, (muggle_atomic_int)sizeof(T)) != 0)
		{
			throw std::runtime_error("failed init memory pool");
		}
	}

	/**
	 * @brief destructor
	 */
	virtual ~ThreadSafeMemoryPool()
	{
		muggle_ts_memory_pool_destroy(&pool_);
	}

	/**
	 * @brief allocate memory without call contructor
	 *
	 * @return allocated memory space
	 */
	virtual void* Allocate() override
	{
		return muggle_ts_memory_pool_alloc(&pool_);
	}

	/**
	 * @brief recycle memory space
	 *
	 * @param p_data pointer to memory space
	 */
	virtual void Recycle(void *p_data) override
	{
		muggle_ts_memory_pool_free(p_data);
	}

private:
	muggle_ts_memory_pool_t pool_;
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_THREADSAFE_MEMORY_POOL_H_ */
