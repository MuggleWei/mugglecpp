#include "muggle/cpp/muggle_cpp.h"
#include <set>
#include <thread>

USING_NS_MUGGLE;

struct FooData
{
	char addr[MUGGLE_SOCKET_ADDR_STRLEN];
};

class FooHandle : public muggle::NetEventHandle
{
public:
	virtual void OnAddCtx(NetEventLoop *, SocketContext *) override
	{
		LOG_INFO("success listen and add context into event loop");
	}

	virtual void OnConnect(NetEventLoop *, SocketContext *ctx) override
	{
		FooData *data = new FooData;
		memset(data->addr, 0, sizeof(data->addr));
		muggle_socket_remote_addr(ctx->GetSocket(), data->addr, sizeof(data->addr), 0);

		LOG_INFO("new connection: %s", data->addr);

		ctx->SetUserData(data);
		socket_ctxs_.insert(ctx);

		// set TCP_NODELAY
		int enable = 1;
		ctx->SetSockOpt(IPPROTO_TCP, TCP_NODELAY, (void*)&enable, sizeof(enable));
	}

	virtual void OnMessage(NetEventLoop *, SocketContext *ctx) override
	{
		FooData *data = (FooData*)ctx->GetUserData();
		char buf[512];
		int n = 0;
		while ((n = ctx->Read(buf, sizeof(buf)-1)) > 0)
		{
			buf[n] = '\0';
			LOG_INFO("on message: addr=%s, msg=%s", data->addr, buf);
			ctx->Write(buf, n);
		}
	}

	virtual void OnClose(NetEventLoop *, SocketContext *ctx) override
	{
		FooData *data = (FooData*)ctx->GetUserData();
		LOG_INFO("disconnect %s", data->addr);
		socket_ctxs_.erase(ctx);
	}

	virtual void OnRelease(NetEventLoop *, SocketContext *ctx) override
	{
		FooData *data = (FooData*)ctx->GetUserData();
		if (data)
		{
			LOG_INFO("release %s", data->addr);
			delete data;
		}
	}

	virtual void OnTimer(NetEventLoop *) override
	{
		LOG_INFO("onTimer");
		const char *msg = "heartbeat";
		size_t len = strlen(msg);
		for (SocketContext *ctx : socket_ctxs_)
		{
			ctx->Write((void*)msg, len);
		}
	}

private:
	std::set<SocketContext*> socket_ctxs_;
};

void run_tcp_server(const char *host, const char *serv)
{
	NetEventLoop event_loop(512, 0);
	event_loop.SetTimerInterval(5000);

	FooHandle handle;
	event_loop.SetHandle((NetEventHandle*)&handle);

	SocketContext *listen_ctx = SocketUtils::TCPListen(host, serv, 512);
	event_loop.AddContext(listen_ctx);

	event_loop.Run();
}

int main(int argc, char *argv[])
{
	// init log
	Log::SimpleInit(LOG_LEVEL_INFO, LOG_LEVEL_DEBUG);

	// init socket
	muggle_socket_lib_init();

	if (argc < 3)
	{
		LOG_ERROR("usage: %s <host> <serv|port-number>", argv[0]);
		exit(EXIT_FAILURE);
	}
	const char *host = argv[1];
	const char *serv = argv[2];

	run_tcp_server(host, serv);

	return 0;
}
