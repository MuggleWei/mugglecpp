/******************************************************************************
 *  @file         os.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-13
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp os
 *****************************************************************************/

#ifndef MUGGLE_CPP_OS_H_
#define MUGGLE_CPP_OS_H_

#include <string>
#include "muggle/cpp/base/macro.h"

NS_MUGGLE_BEGIN

class Os
{
public:
	/**
	 * @brief get current process path
	 *
	 * @return process path, on failed, return empty string
	 */
	MUGGLE_CPP_EXPORT
	static std::string ProcessPath();

	/**
	 * @brief get current working directory
	 *
	 * @return current working directory, on failed, return empty string
	 */
	MUGGLE_CPP_EXPORT
	static std::string Curdir();

	/**
	 * @brief change working directory
	 *
	 * @param path  target working directory
	 *
	 * @return on success returns 0, otherwise return errno in muggle/c/base/err.h
	 */
	MUGGLE_CPP_EXPORT
	static int Chdir(const char *path);

	/**
	 * @brief recursive create directory named path
	 *
	 * @param path: path need to create
	 *
	 * @return success returns 0, otherwise return errno in muggle/c/base/err.h
	 */
	MUGGLE_CPP_EXPORT
	static int Mkdir(const char *path);

	/**
	 * @brief remove the file path
	 *
	 * @param path  the file need to be remove
	 *
	 * @return success returns 0, otherwise return errno in muggle/c/base/err.h
	 */
	MUGGLE_CPP_EXPORT
	static int Remove(const char *path);

	/**
	 * @brief delete an empty directory
	 *
	 * @param path  directory need to be delete
	 *
	 * @return success returns 0, otherwise return errno in muggle/c/base/err.h
	 */
	MUGGLE_CPP_EXPORT
	static int Rmdir(const char *path);

	/**
	 * @brief rename the file or directory src to dst
	 *
	 * @param src  source file path
	 * @param dst  destination fiel path
	 *
	 * @return success returns 0, otherwise return errno in muggle/c/base/err.h
	 */
	MUGGLE_CPP_EXPORT
	static int Rename(const char *src, const char *dst);
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_OS_H_ */
