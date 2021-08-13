/******************************************************************************
 *  @file         dl.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-13
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp dl
 *****************************************************************************/

#ifndef MUGGLE_CPP_DL_H_
#define MUGGLE_CPP_DL_H_

#include "muggle/cpp/base/macro.h"

NS_MUGGLE_BEGIN

class Dl
{
public:
	/**
	 * @brief load dynamic shared object
	 *
	 * @param path filepath of dynamic/shared library
	 *
	 * @return handle for the loaded library
	 */
	MUGGLE_CPP_EXPORT
	static void* load(const char *path);

	/**
	 * @brief 
	 * takes a "handle" of a dynamic loaded shared object returned by 
	 * muggle_dl_load along with a null-terminated symbol name
	 *
	 * @param handle  library handle
	 * @param symbol  symbol in library
	 *
	 * @return address associated with symbol
	 */
	MUGGLE_CPP_EXPORT
	static void* sym(void *handle, const char *symbol);

	/**
	 * @brief 
	 * decrements the reference count on the dynamically loaded shared
	 * object referred to by handle
	 *
	 * @param handle library handle
	 *
	 * @return 
	 *     - return 0 on success
	 *     - otherwise return error code in muggle/c/base/err.h
	 */
	MUGGLE_CPP_EXPORT
	static int close(void *handle);
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_DL_H_ */
