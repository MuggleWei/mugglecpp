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

#include "muggle/cpp/base/macro.h"
#include "muggle/c/memory/threadsafe_memory_pool.h"

NS_MUGGLE_BEGIN

/**
 * @brief  mugglecpp threadsafe memory pool
 */
template<typename T>
class ThreadSafeMemoryPool
{
public:
	/**
	 * @brief memory pool contructor
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
	void* Allocate()
	{
		return muggle_ts_memory_pool_alloc(&pool_);
	}

	/**
	 * @brief recycle memory space
	 *
	 * @param p_data pointer to memory space
	 */
	void Recycle(void *p_data)
	{
		muggle_ts_memory_pool_free(p_data);
	}

	/**
	 * @brief allocate memory space and new
	 *
	 * @param args arguments pass into Class T contructor
	 *
	 * @return new memory space
	 */
	template<typename... Args>
	T* New(Args&&... args)
	{
		void *p_data = this->Allocate();
		if (p_data == nullptr)
		{
			return nullptr;
		}

		return new (p_data) T(std::forward<Args>(args)...);
	}

	/**
	 * @brief destructor and recycle space
	 *
	 * @param p
	 */
	void Erase(T *p)
	{
		p->~T();
		this->Recycle(p);
	}

private:
	muggle_ts_memory_pool_t pool_;
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_THREADSAFE_MEMORY_POOL_H_ */
