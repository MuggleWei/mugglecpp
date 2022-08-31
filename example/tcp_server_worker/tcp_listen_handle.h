#ifndef TCP_LISTEN_HANDLE_H_
#define TCP_LISTEN_HANDLE_H_

#include "muggle/cpp/muggle_cpp.h"
#include <atomic>
#include <set>
#include <vector>

USING_NS_MUGGLE;

class TCPListenHandle : public muggle::NetEventHandle
{
public:
	TCPListenHandle();
	virtual ~TCPListenHandle();

	void SetWorkers(std::vector<NetEventLoop*> *workers);

	virtual void OnAddCtx(NetEventLoop *evloop, SocketContext *ctx) override;

	virtual void OnConnect(NetEventLoop *evloop, SocketContext *ctx) override;

	virtual void OnMessage(NetEventLoop *evloop, SocketContext *ctx) override;

	virtual void OnClose(NetEventLoop *evloop, SocketContext *ctx) override;

private:
	std::vector<NetEventLoop*> *worker_evloops_;
	int worker_idx_;
};

#endif // !FOO_TCP_LISTEN_HANDLE_H_
