/******************************************************************************
 *  @file         memory_pool.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-08
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp memory pool
 *****************************************************************************/

#ifndef MUGGLE_CPP_MEMORY_POOL_H_
#define MUGGLE_CPP_MEMORY_POOL_H_

#include <stdexcept>
#include <utility>

#include "muggle/cpp/base/macro.h"
#include "muggle/c/memory/memory_pool.h"

NS_MUGGLE_BEGIN

/**
 * @brief mugglecpp memory pool
 *
 * NOTE: this memory pool is not threadsafe
 */
template<typename T>
class MemoryPool
{
public:
	/**
	 * @brief memory pool contructor
	 *
	 * @param capacity   intialize capacity of memory pool
	 * @param const_cap  use constant capacity
	 */
	MemoryPool(unsigned int capacity=8, bool const_cap = true)
	{
		if (!muggle_memory_pool_init(&pool_, capacity, (unsigned int)sizeof(T)))
		{
			throw std::runtime_error("failed init memory pool");
		}

		if (const_cap)
		{
			muggle_memory_pool_set_flag(&pool_, MUGGLE_MEMORY_POOL_CONSTANT_SIZE);
		}
	}
	/**
	 * @brief destructor
	 */
	virtual ~MemoryPool()
	{
		muggle_memory_pool_destroy(&pool_);
	}

	/**
	 * @brief allocate memory without call contructor
	 *
	 * @return allocated memory space
	 */
	void* Allocate()
	{
		return muggle_memory_pool_alloc(&pool_);
	}

	/**
	 * @brief recycle memory space
	 *
	 * @param p_data pointer to memory space
	 */
	void Recycle(void *p_data)
	{
		muggle_memory_pool_free(&pool_, p_data);
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

	/**
	 * @brief capacity of memory pool
	 *
	 * @return capacity of memory pool
	 */
	unsigned int Capacity()
	{
		return this->pool_.capacity;
	}

	/**
	 * @brief already allocated number
	 *
	 * @return already allocated number
	 */
	unsigned int Used()
	{
		return this->pool_.used;
	}

private:
	muggle_memory_pool_t pool_;
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_MEMORY_POOL_H_ */
