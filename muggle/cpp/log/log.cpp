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

static int log_fmt_func(const muggle_log_msg_t *msg, char *buf, size_t bufsize)
{
	const char *level = muggle_log_level_to_str(msg->level);

	char filename[MUGGLE_MAX_PATH];
	muggle_path_basename(msg->src_loc.file, filename, sizeof(filename));

	struct tm t;
	gmtime_r(&msg->ts.tv_sec, &t);

	const char *payload = "";
	if (msg->payload)
	{
		payload = msg->payload;
	}

	return (int)snprintf(buf, bufsize,
		"%s|%d-%02d-%02dT%02d:%02d:%02d.%03d|%s.%u|%llu - %s\n",
		level,
		(int)t.tm_year+1900, (int)t.tm_mon+1, (int)t.tm_mday,
		(int)t.tm_hour, (int)t.tm_min, (int)t.tm_sec,
		(int)msg->ts.tv_nsec / 1000000,
		filename, (unsigned int)msg->src_loc.line,
		(unsigned long long)msg->tid,
		payload);
}

bool Log::SimpleInit(int level_console, const char *filepath, int level_file)
{
	muggle_logger_t *logger = muggle_logger_default();

	// fmt
	static muggle_log_fmt_t formatter = {
		MUGGLE_LOG_FMT_ALL,
		log_fmt_func
	};

	// console handler
	static muggle_log_console_handler_t console_handler;
	muggle_log_console_handler_init(&console_handler, 0);
	muggle_log_handler_set_fmt((muggle_log_handler_t*)&console_handler, &formatter);
	muggle_log_handler_set_level((muggle_log_handler_t*)&console_handler,
		level_console);

	logger->add_handler(logger, (muggle_log_handler_t*)&console_handler);

	// file time rotate handler
	static muggle_log_file_time_rot_handler_t time_rot_handler;
	if (filepath != NULL)
	{
		muggle_log_file_time_rot_handler_init(
				&time_rot_handler, filepath,
				MUGGLE_LOG_TIME_ROTATE_UNIT_DAY, 1, false);
		muggle_log_handler_set_fmt((muggle_log_handler_t*)&time_rot_handler, &formatter);
		muggle_log_handler_set_level((muggle_log_handler_t*)&time_rot_handler,
				level_file);

		logger->add_handler(logger, (muggle_log_handler_t*)&time_rot_handler);
	}

	return true;
}

NS_MUGGLE_END
