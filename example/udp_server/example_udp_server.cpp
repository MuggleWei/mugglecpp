#include "muggle/cpp/muggle_cpp.h"

USING_NS_MUGGLE;

class FooHandle : public muggle::SocketHandle
{
public:
	virtual void onMessage(muggle_socket_event_t *, SocketPeer *peer) override
	{
		struct sockaddr_storage addr;
		muggle_socklen_t len = sizeof(addr);
		char buf[512];
		int n = 0;
		while ((n = peer->recvFrom(buf, sizeof(buf), 0, (struct sockaddr*)&addr, &len)) > 0)
		{
			getAddrStr((struct sockaddr*)&addr, str_addr, sizeof(str_addr));
			LOG_INFO("on message: addr=%s, msg=%s", str_addr, buf);
			peer->sendTo(buf, sizeof(buf), 0, (struct sockaddr*)&addr, len);
		}
	}

	virtual void onTimer(muggle_socket_event_t *) override
	{
		LOG_INFO("onTimer");
	}

	virtual void onClose(muggle_socket_event_t *, SocketPeer *) override
	{
		LOG_WARNING("onClose");
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

int main(int argc, char *argv[])
{
	// init log
	Log::SimpleInit(LOG_LEVEL_INFO, "log/example_udp_server.log", LOG_LEVEL_INFO);

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

	UdpServer udp_server;
	udp_server.setHandle(&handle);
	udp_server.setBindAddr(host, serv);
	udp_server.setTimer(5000);
	udp_server.setHintsMaxPeer(1024);
	udp_server.setSndBuf(8 * 1024 * 1024);
	udp_server.setRcvBuf(8 * 1024 * 1024);
	udp_server.run();

	return 0;
}
