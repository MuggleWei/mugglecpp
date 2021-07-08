/******************************************************************************
 *  @file         log.cpp
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-08
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp log
 *****************************************************************************/

#include "log.h"

#include "muggle/c/muggle_c.h"

NS_MUGGLE_BEGIN

bool Log::SimpleInit(int level_console, int level_file_rotating)
{
	return muggle_log_simple_init(level_console, level_file_rotating);
}

NS_MUGGLE_END
