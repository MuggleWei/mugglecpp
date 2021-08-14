#include "muggle/cpp/muggle_cpp.h"
#include <set>

USING_NS_MUGGLE;

struct FooData
{
	char addr[MUGGLE_SOCKET_ADDR_STRLEN];
};

class FooHandle : public muggle::SocketHandle
{
public:
	virtual void onListen(muggle_socket_event_t*, SocketPeer *peer) override
	{
		char buf[MUGGLE_SOCKET_ADDR_STRLEN];
		struct sockaddr *addr = (struct sockaddr*)&peer->getPeer()->addr;
		if (muggle_socket_ntop(
			addr, buf, MUGGLE_SOCKET_ADDR_STRLEN, 0) == NULL)
		{
			snprintf(buf, MUGGLE_SOCKET_ADDR_STRLEN, "unknown:unknown");
		}

		LOG_INFO("success listen: addr=%s", buf);
	}

	virtual void onConnect(muggle_socket_event_t *, SocketPeer *peer) override
	{
		FooData *data = new FooData;
		memset(data->addr, 0, sizeof(data->addr));
		struct sockaddr *addr = (struct sockaddr*)&peer->getPeer()->addr;
		if (muggle_socket_ntop(
				addr, data->addr, MUGGLE_SOCKET_ADDR_STRLEN, 0) == NULL)
		{
			snprintf(data->addr, MUGGLE_SOCKET_ADDR_STRLEN, "unknown:unknown");
		}

		peer->setUserData(data);

		LOG_INFO("connect: %s", data->addr);
		peers_.insert(peer);
	}

	virtual void onError(muggle_socket_event_t *, SocketPeer *peer) override
	{
		FooData *data = (FooData*)peer->getUserData();
		LOG_WARNING("disconnect %s", data->addr);
		peers_.erase(peer);
	}

	virtual void onMessage(muggle_socket_event_t *, SocketPeer *peer) override
	{
		FooData *data = (FooData*)peer->getUserData();
		char buf[512];
		int n = 0;
		while ((n = peer->recv(buf, sizeof(buf), 0)) > 0)
		{
			LOG_INFO("on message: addr=%s, msg=%s", data->addr, buf);
			peer->send(buf, sizeof(buf), 0);
		}
	}

	virtual void onTimer(muggle_socket_event_t *) override
	{
		LOG_INFO("onTimer");
		const char *msg = "heartbeat";
		size_t len = strlen(msg) + 1;
		for (SocketPeer *peer : peers_)
		{
			peer->send(msg, len, 0);
		}
	}

	virtual void onClose(muggle_socket_event_t *, SocketPeer *peer) override
	{
		FooData *data = (FooData*)peer->getUserData();
		LOG_WARNING("close %s", data->addr);
		delete data;
	}

private:
	std::set<SocketPeer*> peers_;
};

int main(int argc, char *argv[])
{
	// init log
	Log::SimpleInit(LOG_LEVEL_INFO, "log/example_tcp_server.log", LOG_LEVEL_INFO);

	// init socket
	muggle_socket_lib_init();

	if (argc < 3)
	{
		LOG_ERROR("usage: %s <host> <serv|port-number>", argv[0]);
		exit(EXIT_FAILURE);
	}
	const char *host = argv[1];
	const char *serv = argv[2];

	FooHandle handle;

	TcpServer tcp_server;
	tcp_server.setHandle(&handle);
	tcp_server.setListenAddr(host, serv);
	tcp_server.setTcpNoDelay(true);
	tcp_server.setTimer(5000);
	tcp_server.setHintsMaxPeer(1024);
	tcp_server.run();

	return 0;
}
