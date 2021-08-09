/******************************************************************************
 *  @file         interface_memory_pool.hpp
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-09
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp memory pool interface
 *****************************************************************************/

#ifndef MUGGLE_CPP_INTERFACE_MEMORY_POOL_H_
#define MUGGLE_CPP_INTERFACE_MEMORY_POOL_H_

#include <utility>

#include "muggle/cpp/base/macro.h"

NS_MUGGLE_BEGIN

template<typename T>
class IMemoryPool
{
public:
	/**
	 * @brief allocate memory without call constructor
	 *
	 * @return 
	 */
	virtual void *Allocate() = 0;

	/**
	 * @brief recycle memory space
	 *
	 * @param p_data  pointer to memory space
	 */
	virtual void Recycle(void *p_data) = 0;

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
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_INTERFACE_MEMORY_POOL_H_ */
