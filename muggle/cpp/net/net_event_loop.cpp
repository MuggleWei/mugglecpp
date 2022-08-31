#include "net_event_loop.h"
#include <stdexcept>
#include <stdlib.h>
#include <string.h>

NS_MUGGLE_BEGIN

static void NetEventLoopOnAddCtx(muggle_event_loop_t *evloop, muggle_socket_context_t *ctx)
{
	SocketContext *socket_ctx = (SocketContext*)muggle_socket_ctx_get_data(ctx);
	NetEventLoop *net_evloop = (NetEventLoop*)muggle_evloop_get_data(evloop);
	NetEventHandle *handle = net_evloop->GetHandle();
	if (handle)
	{
		handle->OnAddCtx(net_evloop, socket_ctx);
	}
}

static void NetEventLoopOnConn(muggle_event_loop_t *evloop, muggle_socket_context_t *ctx)
{
	SocketContext *socket_ctx = new SocketContext(ctx);

	NetEventLoop *net_evloop = (NetEventLoop*)muggle_evloop_get_data(evloop);
	NetEventHandle *handle = net_evloop->GetHandle();
	if (handle)
	{
		handle->OnConnect(net_evloop, socket_ctx);
	}
}

static void NetEventLoopOnMsg(muggle_event_loop_t *evloop, muggle_socket_context_t *ctx)
{
	SocketContext *socket_ctx = (SocketContext*)muggle_socket_ctx_get_data(ctx);
	NetEventLoop *net_evloop = (NetEventLoop*)muggle_evloop_get_data(evloop);
	NetEventHandle *handle = net_evloop->GetHandle();
	if (handle)
	{
		handle->OnMessage(net_evloop, socket_ctx);
	}
}

static void NetEventLoopOnClose(muggle_event_loop_t *evloop, muggle_socket_context_t *ctx)
{
	SocketContext *socket_ctx = (SocketContext*)muggle_socket_ctx_get_data(ctx);
	NetEventLoop *net_evloop = (NetEventLoop*)muggle_evloop_get_data(evloop);
	NetEventHandle *handle = net_evloop->GetHandle();
	if (handle)
	{
		handle->OnClose(net_evloop, socket_ctx);
	}
}

static void NetEventLoopOnRlease(muggle_event_loop_t *evloop, muggle_socket_context_t *ctx)
{
	SocketContext *socket_ctx = (SocketContext*)muggle_socket_ctx_get_data(ctx);
	NetEventLoop *net_evloop = (NetEventLoop*)muggle_evloop_get_data(evloop);
	NetEventHandle *handle = net_evloop->GetHandle();
	if (handle)
	{
		handle->OnRelease(net_evloop, socket_ctx);
	}

	delete socket_ctx;
}

static void NetEventLoopOnTimer(muggle_event_loop_t *evloop)
{
	NetEventLoop *net_evloop = (NetEventLoop*)muggle_evloop_get_data(evloop);
	NetEventHandle *handle = net_evloop->GetHandle();
	if (handle)
	{
		handle->OnTimer(net_evloop);
	}
}

static muggle_socket_context_t* NetEventLoopAlloc(void *pool)
{
	return (muggle_socket_context_t*)malloc(sizeof(muggle_socket_context_t));
}

static void NetEventLoopFree(void *pool, muggle_socket_context_t *data)
{
	free(data);
}

NetEventLoop::NetEventLoop(int hints_max_fd, bool use_mem_pool)
	: evloop_(nullptr)
	, handle_(nullptr)
	, net_event_handle_(nullptr)
	, user_data_(nullptr)
{
	// init event loop
	muggle_event_loop_init_args_t ev_init_args;
	memset(&ev_init_args, 0, sizeof(ev_init_args));
	ev_init_args.evloop_type = MUGGLE_EVLOOP_TYPE_NULL;
	ev_init_args.hints_max_fd = hints_max_fd;
	ev_init_args.use_mem_pool = use_mem_pool ? 1 : 0;

	evloop_ = muggle_evloop_new(&ev_init_args);
	if (evloop_ == nullptr)
	{
		throw std::runtime_error("failed new muggle event loop");
	}
	muggle_evloop_set_data(evloop_, this);

	// init socket event loop handle
	handle_ = (muggle_socket_evloop_handle_t*)malloc(sizeof(muggle_socket_evloop_handle_t));
	if (handle_ == nullptr)
	{
		throw std::runtime_error("failed allocate space for socket event loop handle");
	}

	if (muggle_socket_evloop_handle_init(handle_) != 0)
	{
		free(handle_);
		handle_ = nullptr;
		throw std::runtime_error("failed init socket event loop handle");
	}
	muggle_socket_evloop_handle_set_cb_add_ctx(handle_, NetEventLoopOnAddCtx);
	muggle_socket_evloop_handle_set_cb_conn(handle_, NetEventLoopOnConn);
	muggle_socket_evloop_handle_set_cb_msg(handle_, NetEventLoopOnMsg);
	muggle_socket_evloop_handle_set_cb_close(handle_, NetEventLoopOnClose);
	muggle_socket_evloop_handle_set_cb_release(handle_, NetEventLoopOnRlease);
	muggle_socket_evloop_handle_set_cb_timer(handle_, NetEventLoopOnTimer);

	muggle_socket_evloop_handle_set_alloc_free(
		handle_, this, NetEventLoopAlloc, NetEventLoopFree);

	muggle_socket_evloop_handle_attach(handle_, evloop_);
}

NetEventLoop::~NetEventLoop()
{
	if (handle_)
	{
		muggle_socket_evloop_handle_destroy(handle_);
		free(handle_);
		handle_ = nullptr;
	}

	if (evloop_)
	{
		muggle_evloop_delete(evloop_);
		evloop_ = nullptr;
	}
}

void NetEventLoop::SetHandle(NetEventHandle *handle)
{
	net_event_handle_ = handle;
}

NetEventHandle* NetEventLoop::GetHandle()
{
	return net_event_handle_;
}

void NetEventLoop::SetUserData(void *user_data)
{
	user_data_ = user_data;
}

void* NetEventLoop::GetUserData()
{
	return user_data_;
}

void NetEventLoop::AddContext(SocketContext *socket_ctx)
{
	muggle_socket_context_t *ctx = socket_ctx->GetContext();
	muggle_socket_evloop_add_ctx(evloop_, ctx);
}

void NetEventLoop::Run()
{
	if (evloop_ == nullptr || handle_ == nullptr)
	{
		return;
	}

	muggle_evloop_run(evloop_);
}

void NetEventLoop::Exit()
{
	muggle_evloop_exit(evloop_);
}

void NetEventLoop::SetTimerInterval(int ms)
{
	muggle_socket_evloop_handle_set_timer_interval(handle_, ms);
	muggle_evloop_set_timer_interval(evloop_, ms);
}

NS_MUGGLE_END
