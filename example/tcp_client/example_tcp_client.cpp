#include "muggle/cpp/muggle_cpp.h"

USING_NS_MUGGLE;

struct FooData
{
	char addr[MUGGLE_SOCKET_ADDR_STRLEN];
};

class FooHandle : public muggle::SocketHandle
{
public:
	virtual void onConnect(muggle_socket_event_t *, SocketPeer *peer) override
	{
		FooData *data = new FooData;
		memset(data->addr, 0, sizeof(data->addr));
		struct sockaddr *addr = (struct sockaddr*)&peer->getPeer()->addr;
		if (muggle_socket_ntop(
				addr,data->addr, MUGGLE_SOCKET_ADDR_STRLEN, 0) == NULL)
		{
			snprintf(data->addr, MUGGLE_SOCKET_ADDR_STRLEN, "unknown:unknown");
		}

		peer->setUserData(data);

		conn_peer_ = peer;
	}

	/**
	 * @brief socket callback function - onError
	 */
	MUGGLE_CPP_EXPORT
	virtual void onError(muggle_socket_event_t *, SocketPeer *peer) override
	{
		FooData *data = (FooData*)peer->getUserData();
		LOG_WARNING("disconnect %s", data->addr);
	}

	/**
	 * @brief socket callback function - onMessage
	 */
	MUGGLE_CPP_EXPORT
	virtual void onMessage(muggle_socket_event_t *, SocketPeer *peer) override
	{
		FooData *data = (FooData*)peer->getUserData();
		char buf[512];
		int n = 0;
		while ((n = peer->recv(buf, sizeof(buf), 0)) > 0)
		{
			LOG_INFO("on message: addr=%s, msg=%s", data->addr, buf);
		}
	}

	/**
	 * @brief socket callback function - onTimer
	 */
	MUGGLE_CPP_EXPORT
	virtual void onTimer(muggle_socket_event_t *) override
	{
		if (conn_peer_)
		{
			const char *msg = "hello";
			LOG_INFO("timer send: msg=%s", msg);
			conn_peer_->send(msg, strlen(msg) + 1, 0);
		}
	}

	/**
	 * @brief socket callback function - onClose
	 */
	MUGGLE_CPP_EXPORT
	virtual void onClose(muggle_socket_event_t *, SocketPeer *peer) override
	{
		FooData *data = (FooData*)peer->getUserData();
		LOG_WARNING("close %s", data->addr);
		delete data;

		conn_peer_ = nullptr;
	}

private:
	SocketPeer *conn_peer_;
};

int main(int argc, char *argv[])
{
	// init log
	Log::SimpleInit(LOG_LEVEL_INFO, "log/example_tcp_client.log", LOG_LEVEL_INFO);

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

	TcpClient tcp_client;
	tcp_client.setHandle(&handle);
	tcp_client.setConnectAddr(host, serv);
	tcp_client.setTcpNoDelay(true);
	tcp_client.setTimer(1000);
	tcp_client.setAutoReconnect(true, 3000);
	tcp_client.setConnectTimeout(3);
	tcp_client.run();

	return 0;
}
