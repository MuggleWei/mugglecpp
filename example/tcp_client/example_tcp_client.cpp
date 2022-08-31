#include "muggle/cpp/muggle_cpp.h"
#include <thread>
#include <chrono>

USING_NS_MUGGLE;

struct FooData
{
	char addr[MUGGLE_SOCKET_ADDR_STRLEN];
};

class FooHandle : public muggle::NetEventHandle
{
public:
	virtual void OnAddCtx(NetEventLoop *, SocketContext *ctx) override
	{
		FooData *data = new FooData;
		memset(data->addr, 0, sizeof(data->addr));
		muggle_socket_remote_addr(ctx->GetSocket(), data->addr, sizeof(data->addr), 0);

		LOG_INFO("success connect to %s", data->addr);

		ctx->SetUserData(data);
		conn_ctx_ = ctx;

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
		}
	}

	virtual void OnClose(NetEventLoop *, SocketContext *ctx) override
	{
		FooData *data = (FooData*)ctx->GetUserData();
		LOG_WARNING("disconnect %s", data->addr);

		Connect();
	}

	virtual void OnRelease(NetEventLoop *, SocketContext *ctx) override
	{
		FooData *data = (FooData*)ctx->GetUserData();
		if (data)
		{
			LOG_WARNING("release %s", data->addr);
			delete data;
		}
		conn_ctx_ = nullptr;
	}

	virtual void OnTimer(NetEventLoop *) override
	{
		if (conn_ctx_)
		{
			const char *msg = "hello";
			LOG_INFO("timer send: msg=%s", msg);
			conn_ctx_->Write((void*)msg, strlen(msg));
		}
	}

	void SetServerAddr(const char *host, const char *serv)
	{
		host_ = host;
		serv_ = serv;
	}

	void SetEventLoop(NetEventLoop *event_loop)
	{
		evloop_ = event_loop;
	}

	void Connect()
	{
		std::thread th([&] {
			while (1)
			{

				SocketContext *conn_ctx =
					SocketUtils::TCPConnect(host_.c_str(), serv_.c_str(), 3);
				if (conn_ctx == nullptr)
				{
					std::this_thread::sleep_for(std::chrono::seconds(3));
					continue;
				}
				evloop_->AddContext(conn_ctx);
				break;
			}
		});
		th.detach();
	}

private:
	SocketContext *conn_ctx_;

	NetEventLoop *evloop_;
	std::string host_;
	std::string serv_;
};

void run_tcp_client(const char *host, const char *serv)
{
	NetEventLoop event_loop(512, 0);
	event_loop.SetTimerInterval(1000);

	FooHandle handle;
	handle.SetEventLoop(&event_loop);
	handle.SetServerAddr(host, serv);
	event_loop.SetHandle((NetEventHandle*)&handle);

	handle.Connect();

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

	run_tcp_client(host, serv);

	return 0;
}
