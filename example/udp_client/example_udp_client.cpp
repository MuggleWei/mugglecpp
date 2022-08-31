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

		ctx->SetUserData(data);

		LOG_INFO("udp connect %s and add context into event loop", data->addr);

		conn_ctx_ = ctx;
	}

	virtual void OnClose(NetEventLoop *, SocketContext *ctx) override
	{
		FooData *data = (FooData*)ctx->GetUserData();
		LOG_WARNING("udp disconnect %s", data->addr);

		Connect();
	}

	virtual void OnRelease(NetEventLoop *, SocketContext *ctx) override
	{
		FooData *data = (FooData*)ctx->GetUserData();
		LOG_WARNING("release %s", data->addr);
		delete data;

		conn_ctx_ = nullptr;
	}

	virtual void OnMessage(NetEventLoop *, SocketContext *ctx) override
	{
		FooData *data = (FooData*)ctx->GetUserData();
		char buf[512];
		int n = 0;
		while ((n = ctx->Recv(buf, sizeof(buf)-1, 0)) > 0)
		{
			buf[n] = '\0';
			LOG_INFO("on message: addr=%s, msg=%s", data->addr, buf);
		}
	}

	virtual void OnTimer(NetEventLoop *) override
	{
		if (conn_ctx_)
		{
			const char *msg = "hello";
			LOG_INFO("timer send: msg=%s", msg);
			conn_ctx_->Send((void*)msg, strlen(msg), 0);
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
				SocketContext *conn_ctx = SocketUtils::UDPConnect(host_.c_str(), serv_.c_str());
				if (conn_ctx == nullptr)
				{
					std::this_thread::sleep_for(std::chrono::seconds(3));
					continue;
				}

				// set SO_SNDBUF and SO_RCVBUF
				int sndbuf_size = 8 * 1024 * 1024;
				int ret = conn_ctx->SetSockOpt(SOL_SOCKET, SO_SNDBUF, (void*)&sndbuf_size, sizeof(sndbuf_size));
				if (ret != 0)
				{
				LOG_ERROR("failed set SO_SNDBUF");
				exit(EXIT_FAILURE);
				}

				int rcvbuf_size = 8 * 1024 * 1024;
				ret = conn_ctx->SetSockOpt(SOL_SOCKET, SO_RCVBUF, (void*)&rcvbuf_size, sizeof(rcvbuf_size));
				if (ret != 0)
				{
					LOG_ERROR("failed set SO_RCVBUF");
					exit(EXIT_FAILURE);
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

void run_udp_client(const char *host, const char *serv)
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

	run_udp_client(host, serv);

	return 0;
}
