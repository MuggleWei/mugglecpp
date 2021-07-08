/******************************************************************************
 *  @file         version.cpp
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-08
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp version
 *****************************************************************************/

#include "version.h"

NS_MUGGLE_BEGIN

#ifndef MUGGLE_CPP_SEMVER
	#define MUGGLE_CPP_SEMVER ?.?.?
#endif
#define MUGGLE_CPP_COMPILRE_TIME __DATE__ " " __TIME__

const char* mugglecpp_version()
{
	return MUGGLE_MACRO_STR(MUGGLE_CPP_SEMVER);
}

const char* mugglecpp_compile_time()
{
	return MUGGLE_CPP_COMPILRE_TIME;
}

NS_MUGGLE_END
