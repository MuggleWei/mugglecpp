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
#include "muggle/c/log/log.h"

NS_MUGGLE_BEGIN

#if MUGGLE_CPP_USE_LOG_MACRO

// use mugglec log by default
#define LOG_TRACE   MUGGLE_LOG_TRACE
#define LOG_INFO    MUGGLE_LOG_INFO
#define LOG_WARNING MUGGLE_LOG_WARNING
#define LOG_ERROR   MUGGLE_LOG_ERROR
#define LOG_FATAL   MUGGLE_LOG_FATAL

#define LOG_LEVEL_TRACE MUGGLE_LOG_LEVEL_TRACE
#define LOG_LEVEL_INFO MUGGLE_LOG_LEVEL_INFO
#define LOG_LEVEL_WARNING MUGGLE_LOG_LEVEL_WARNING
#define LOG_LEVEL_ERROR MUGGLE_LOG_LEVEL_ERROR
#define LOG_LEVEL_FATAL MUGGLE_LOG_LEVEL_FATAL

#endif

class Log
{
public:
	/**
	 * @brief simple initialize log with console and file_rotate category
	 *
	 * @param level_console       console output level
	 * @param level_file_rotating file rotating output level
	 *
	 * @return 
	 *     0 - success
	 *     otherwise - failed
	 */
	MUGGLE_CPP_EXPORT
	static bool SimpleInit(int level_console, int level_file_rotatin);
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_LOG_H_ */
