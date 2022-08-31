/******************************************************************************
 *  @file         path.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-13
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp path
 *****************************************************************************/

#ifndef MUGGLE_CPP_PATH_H_
#define MUGGLE_CPP_PATH_H_

#include <string>
#include "muggle/cpp/base/macro.h"

NS_MUGGLE_BEGIN

class Path
{
public:
	/**
	 * @brief return a normalized absolutized version of the path
	 *
	 * @param path  the original path
	 *
	 * @return
	 *     - on success, return absolutized path
	 *     - on failed, return ""
	 */
	MUGGLE_CPP_EXPORT
	static std::string Abs(const char *path);

	/**
	 * @brief return the base name of pathname path
	 *
	 * @param path  the original path
	 *
	 * @return
	 *     - on success, return base name
	 *     - on failed, return ""
	 */
	MUGGLE_CPP_EXPORT
	static std::string Basename(const char *path);

	/**
	 * @brief return the dirname of pathname path
	 *
	 * @param path  the original path
	 *
	 * @return
	 *     - on success, return dirname of path
	 *     - on failed, return ""
	 */
	MUGGLE_CPP_EXPORT
	static std::string Dirname(const char *path);

	/**
	 * @brief check whether the path is absolutized version of path
	 *
	 * @param path file path
	 *
	 * @return boolean value
	 */
	MUGGLE_CPP_EXPORT 
	static bool IsAbs(const char *path);

	/**
	 * @brief check whether the path exists
	 *
	 * @param path file path
	 *
	 * @return boolean value
	 */
	MUGGLE_CPP_EXPORT
	static bool Exists(const char *path);

	/**
	 * @brief join two path
	 *
	 * @param path1  path 1
	 * @param path2  path 2
	 *
	 * @return
	 *     - on success, return dirname of path
	 *     - on failed, return ""
	 */
	MUGGLE_CPP_EXPORT
	static std::string Join(const char *path1, const char *path2);

	/**
	 * @brief normalize a pathname
	 *
	 * @param path  original path
	 * @param ret   normalized path
	 *
	 * @return
	 *     - on success, return dirname of path
	 *     - on failed, return ""
	 */
	MUGGLE_C_EXPORT
	static std::string Norm(const char *path);
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_PATH_H_ */
