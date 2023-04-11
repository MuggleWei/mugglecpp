/******************************************************************************
 *  @file         macro.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-08
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp macro
 *****************************************************************************/

#ifndef MUGGLE_CPP_MACRO_H_
#define MUGGLE_CPP_MACRO_H_

#include "muggle/c/base/macro.h"
#include "muggle/cpp/mugglecpp_config.h"

// lib and dll
#if MUGGLE_PLATFORM_WINDOWS && defined(MUGGLE_CPP_USE_DLL)
	#ifdef MUGGLE_CPP_EXPORTS
		#define MUGGLE_CPP_EXPORT __declspec(dllexport)
	#else
		#define MUGGLE_CPP_EXPORT __declspec(dllimport)
	#endif
#else
	#define MUGGLE_CPP_EXPORT
#endif

#endif /* ifndef MUGGLE_CPP_MACRO_H_ */
