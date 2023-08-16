#include "net_event_handle.h"

NS_MUGGLE_BEGIN

NetEventHandle::NetEventHandle()
{}

NetEventHandle::~NetEventHandle()
{}

void NetEventHandle::OnAddCtx(NetEventLoop *evloop, SocketContext *ctx)
{
	MUGGLE_UNUSED(evloop);
	MUGGLE_UNUSED(ctx);
}

void NetEventHandle::OnConnect(NetEventLoop *evloop, SocketContext *ctx)
{
	MUGGLE_UNUSED(evloop);
	MUGGLE_UNUSED(ctx);
}

void NetEventHandle::OnMessage(NetEventLoop *evloop, SocketContext *ctx)
{
	MUGGLE_UNUSED(evloop);
	MUGGLE_UNUSED(ctx);
}

void NetEventHandle::OnClose(NetEventLoop *evloop, SocketContext *ctx)
{
	MUGGLE_UNUSED(evloop);
	MUGGLE_UNUSED(ctx);
}

void NetEventHandle::OnRelease(NetEventLoop *evloop, SocketContext *ctx)
{
	MUGGLE_UNUSED(evloop);
	MUGGLE_UNUSED(ctx);
}

void NetEventHandle::OnTimer(NetEventLoop *evloop)
{
	MUGGLE_UNUSED(evloop);
}

NS_MUGGLE_END
