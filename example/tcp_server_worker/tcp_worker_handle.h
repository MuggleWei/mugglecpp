#ifndef TCP_WORKDER_HANDLE_H_
#define TCP_WORKDER_HANDLE_H_

#include "muggle/cpp/muggle_cpp.h"

USING_NS_MUGGLE;

class TCPWorkerHandle : public muggle::NetEventHandle
{
public:
	virtual void OnAddCtx(NetEventLoop *evloop, SocketContext *ctx) override;
	virtual void OnMessage(NetEventLoop *evloop, SocketContext *ctx) override;
	virtual void OnClose(NetEventLoop *evloop, SocketContext *ctx) override;
	virtual void OnRelease(NetEventLoop *evloop, SocketContext *ctx) override;

	void SetWorkerId(int worker_id);

private:
	int worker_id_;
};

#endif // !FOO_TCP_WORKDER_HANDLE_H_
