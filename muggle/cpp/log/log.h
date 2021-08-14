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

#ifdef MUGGLE_CPP_USE_LOG_MACRO

// use mugglec log by default
#define LOG_TRACE(format, ...) MUGGLE_LOG_DEFAULT(MUGGLE_LOG_LEVEL_TRACE, format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) MUGGLE_LOG_DEFAULT(MUGGLE_LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) MUGGLE_LOG_DEFAULT(MUGGLE_LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...) MUGGLE_LOG_DEFAULT(MUGGLE_LOG_LEVEL_WARNING, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) MUGGLE_LOG_DEFAULT(MUGGLE_LOG_LEVEL_ERROR, format, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) MUGGLE_LOG_DEFAULT(MUGGLE_LOG_LEVEL_FATAL, format, ##__VA_ARGS__)

#define LOG_LEVEL_TRACE MUGGLE_LOG_LEVEL_TRACE
#define LOG_LEVEL_DEBUG MUGGLE_LOG_LEVEL_DEBUG
#define LOG_LEVEL_INFO MUGGLE_LOG_LEVEL_INFO
#define LOG_LEVEL_WARNING MUGGLE_LOG_LEVEL_WARNING
#define LOG_LEVEL_ERROR MUGGLE_LOG_LEVEL_ERROR
#define LOG_LEVEL_FATAL MUGGLE_LOG_LEVEL_FATAL

#endif

class Log
{
public:
	/**
	 * @brief simple initialize log with console and file time rotate handler
	 *
	 * @param level_console  console output level
	 * @param filepath       file path, if NULL, don't use file time roate handler
	 * @param level_file     file time rotating output level
	 *
	 * @return boolean value
	 */
	MUGGLE_CPP_EXPORT
	static bool SimpleInit(int level_console, const char *filepath, int level_file);
};

NS_MUGGLE_END

#endif /* ifndef MUGGLE_CPP_LOG_H_ */
