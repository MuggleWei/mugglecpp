#include "tcp_listen_handle.h"
#include "struct.h"

static void DetachSocketContext(SocketContext *ctx)
{
	server_socket_data_t *user_data = (server_socket_data_t*)ctx->GetUserData();
	user_data->detached = true;

	ctx->RefCntRetain();
	ctx->SetFlagClose();

	LOG_INFO("detach socket context: %s", user_data->addr);
}

TCPListenHandle::TCPListenHandle()
	: worker_idx_(0)
{}
TCPListenHandle::~TCPListenHandle()
{}

void TCPListenHandle::SetWorkers(std::vector<NetEventLoop*> *workers)
{
	worker_evloops_ = workers;
}

void TCPListenHandle::OnAddCtx(NetEventLoop *evloop, SocketContext *ctx)
{
	LOG_INFO("success listen and add context into event loop");
}

void TCPListenHandle::OnConnect(NetEventLoop *evloop, SocketContext *ctx)
{
	// set user data
	server_socket_data_t *data = (server_socket_data_t*)malloc(sizeof(server_socket_data_t));
	memset(data, 0, sizeof(*data));
	data->last_active_ts = time(NULL);
	data->detached = false;
	muggle_socket_remote_addr(ctx->GetSocket(), data->addr, sizeof(data->addr), 0);
	ctx->SetUserData(data);

	LOG_INFO("New connection: %s", data->addr);

	// note: don't detach here, cause connection return not trigger event loop. 
	// if wanna detach after connection immediately, don't use event loop
	// DetachSocketContext(ctx);
}

void TCPListenHandle::OnMessage(NetEventLoop *evloop, SocketContext *ctx)
{
	server_socket_data_t *user_data = (server_socket_data_t*)ctx->GetUserData();
	LOG_INFO("recv message socket[%s], assume login success", user_data->addr);

	// detach
	DetachSocketContext(ctx);
}

void TCPListenHandle::OnClose(NetEventLoop *evloop, SocketContext *ctx)
{
	server_socket_data_t *user_data = (server_socket_data_t*)ctx->GetUserData();

	// detach and move context to worker event loop
	if (user_data && user_data->detached)
	{
		int idx = worker_idx_++;
		idx %= worker_evloops_->size();

		LOG_INFO("move socket context to worker event loop: %s -> %d", user_data->addr, idx);
		user_data->detached = false;
		ctx->ClearFlags();

		NetEventLoop *worker = (*worker_evloops_)[idx];
		worker->AddContext(ctx);
	}
}
