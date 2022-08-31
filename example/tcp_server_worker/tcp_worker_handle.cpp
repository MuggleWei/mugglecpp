#include "tcp_worker_handle.h"
#include "struct.h"

void TCPWorkerHandle::OnAddCtx(NetEventLoop *, SocketContext *ctx)
{
	server_socket_data_t *user_data = (server_socket_data_t*)ctx->GetUserData();
	LOG_INFO("worker[%d] event loop add context %s", worker_id_, user_data->addr);
}
void TCPWorkerHandle::OnMessage(NetEventLoop *evloop, SocketContext *ctx)
{
	server_socket_data_t *user_data = (server_socket_data_t*)ctx->GetUserData();
	char buf[512];
	int n = 0;
	while ((n = ctx->Read(buf, sizeof(buf)-1)) > 0)
	{
		buf[n] = '\0';
		LOG_INFO("on message: addr=%s, msg=%s", user_data->addr, buf);
		ctx->Write(buf, n);
	}
}
void TCPWorkerHandle::OnClose(NetEventLoop *evloop, SocketContext *ctx)
{
	server_socket_data_t *user_data = (server_socket_data_t*)ctx->GetUserData();
	if (user_data)
	{
		LOG_INFO("disconnect %s", user_data->addr);
	}
}
void TCPWorkerHandle::OnRelease(NetEventLoop *evloop, SocketContext *ctx)
{
	server_socket_data_t *user_data = (server_socket_data_t*)ctx->GetUserData();
	if (user_data)
	{
		LOG_INFO("release %s", user_data->addr);
		free(user_data);
	}
}

void TCPWorkerHandle::SetWorkerId(int worker_id)
{
	worker_id_ = worker_id;
}
