#include "muggle/cpp/muggle_cpp.h"

USING_NS_MUGGLE;

class FooHandle : public muggle::NetEventHandle
{
public:
	virtual void OnAddCtx(NetEventLoop *, SocketContext *) override
	{
		LOG_INFO("success bind and add context into event loop");
	}

	virtual void OnMessage(NetEventLoop *, SocketContext *ctx) override
	{
		struct sockaddr_storage addr;
		muggle_socklen_t len = sizeof(addr);
		char buf[512];
		int n = 0;
		while ((n = ctx->RecvFrom(buf, sizeof(buf)-1, 0, (struct sockaddr*)&addr, &len)) > 0)
		{
			buf[n] = '\0';
			getAddrStr((struct sockaddr*)&addr, str_addr, sizeof(str_addr));
			LOG_INFO("on message: addr=%s, msg=%s", str_addr, buf);
			ctx->SendTo(buf, n, 0, (struct sockaddr*)&addr, len);
		}
	}

	virtual void OnTimer(NetEventLoop *) override
	{
		LOG_INFO("onTimer");
	}

private:
	void getAddrStr(struct sockaddr* addr, char *buf, muggle_socklen_t bufsize)
	{
		if (muggle_socket_ntop(addr, buf, bufsize, 0) == NULL)
		{
			snprintf(buf, bufsize, "unknown:unknown");
		}
	}

private:
	char str_addr[MUGGLE_SOCKET_ADDR_STRLEN];
};

void run_udp_server(const char *host, const char *serv)
{
	NetEventLoop event_loop(512, 0);
	event_loop.SetTimerInterval(5000);

	FooHandle handle;
	event_loop.SetHandle((NetEventHandle*)&handle);

	SocketContext *bind_ctx = SocketUtils::UDPBind(host, serv);

	// set SO_SNDBUF and SO_RCVBUF
	int sndbuf_size = 8 * 1024 * 1024;
	int ret = bind_ctx->SetSockOpt(SOL_SOCKET, SO_SNDBUF, (void*)&sndbuf_size, sizeof(sndbuf_size));
	if (ret != 0)
	{
		LOG_ERROR("failed set SO_SNDBUF");
		exit(EXIT_FAILURE);
	}

	int rcvbuf_size = 8 * 1024 * 1024;
	ret = bind_ctx->SetSockOpt(SOL_SOCKET, SO_RCVBUF, (void*)&rcvbuf_size, sizeof(rcvbuf_size));
	if (ret != 0)
	{
		LOG_ERROR("failed set SO_RCVBUF");
		exit(EXIT_FAILURE);
	}

	event_loop.AddContext(bind_ctx);

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

	run_udp_server(host, serv);

	return 0;
}
