#ifndef STRUCT_H_
#define STRUCT_H_

#include "muggle/cpp/muggle_cpp.h"

typedef struct server_socket_data
{
	time_t last_active_ts;
	bool detached;
	char addr[MUGGLE_SOCKET_ADDR_STRLEN];
} server_socket_data_t;

#endif // !FOO_STRUCT_H_
