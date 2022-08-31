/******************************************************************************
 *  @file         log.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-08
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp log
 *****************************************************************************/

#ifndef MUGGLE_CPP_LOG_H_
#define MUGGLE_CPP_LOG_H_

#include "muggle/cpp/base/macro.h"

NS_MUGGLE_BEGIN

class Log
{
public:
	/**
	 * @brief simple initialize log
	 *
	 * invoke this function, will initialize default sync logger
	 * and add console handler and file rotate handler
	 *
	 * @param level_console       console output level, if it's -1, disable console output
	 * @param level_file_rotating file rotating output level, if it's -1, disable file output
	 *
	 * @return 
	 *     0 - success
	 *     otherwise - failed
	 */
	MUGGLE_CPP_EXPORT
	static bool SimpleInit(int level_console, int level_file_rotating);

	/**
	 * @brief complicated initialize log
	 *
	 * @param level_console       console output level, if it's -1, disable console output
	 * @param level_file_rotating file time rotating output level, if it's -1, disable file output
	 * @param log_path            log output path, if it's NULL, log path is $PWD/log/binary_name.log.yyyymmdd
	 *
	 * @return 
	 *     0 - success
	 *     otherwise - failed
	 */
	MUGGLE_CPP_EXPORT
	static bool ComplicatedInit(int level_console, int level_file_time_rotating, const char *log_path);
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_LOG_H_ */
