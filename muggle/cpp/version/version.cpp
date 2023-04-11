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
#include <stdio.h>
#include <string.h>

NS_MUGGLE_BEGIN

#define MUGGLE_CPP_COMPILRE_TIME __DATE__ " " __TIME__

const char* mugglecpp_version()
{
	return MUGGLE_CPP_VERSION;
}

const char* mugglecpp_compile_time()
{
	return MUGGLE_CPP_COMPILRE_TIME;
}

const char* mugglecpp_compile_time_iso8601(char *buf, int bufsize)
{
	if (bufsize < 21)
	{
		return NULL;
	}
	memset(buf, 0, bufsize);

	const char *compile_time = mugglecpp_compile_time();

	// year
	buf[0] = compile_time[7];
	buf[1] = compile_time[8];
	buf[2] = compile_time[9];
	buf[3] = compile_time[10];
	buf[4] = '-';

	// First month letter, Oct Nov Dec = '1' otherwise '0'
	buf[5] = (compile_time[0] == 'O' || compile_time[0] == 'N' || compile_time[0] == 'D') ? '1' : '0';
	// Second month letter
	buf[6] =
		(compile_time[0] == 'J') ? ( (compile_time[1] == 'a') ? '1' :       // Jan, Jun or Jul
				((compile_time[2] == 'n') ? '6' : '7') ) :
		(compile_time[0] == 'F') ? '2' :                                // Feb 
		(compile_time[0] == 'M') ? (compile_time[2] == 'r') ? '3' : '5' :   // Mar or May
		(compile_time[0] == 'A') ? (compile_time[1] == 'p') ? '4' : '8' :   // Apr or Aug
		(compile_time[0] == 'S') ? '9' :                                // Sep
		(compile_time[0] == 'O') ? '0' :                                // Oct
		(compile_time[0] == 'N') ? '1' :                                // Nov
		(compile_time[0] == 'D') ? '2' :                                // Dec
		0;
	buf[7] = '-';

	// First day letter, replace space with digit
	buf[8] = compile_time[4]==' ' ? '0' : compile_time[4];
	// Second day letter
	buf[9] = compile_time[5];
	buf[10] = 'T';

	memcpy(&buf[11], &compile_time[12], 8);

	return buf;
}

NS_MUGGLE_END
