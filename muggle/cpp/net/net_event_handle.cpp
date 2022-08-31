#include "net_event_handle.h"

NS_MUGGLE_BEGIN

void NetEventHandle::OnAddCtx(NetEventLoop *evloop, SocketContext *ctx)
{}

void NetEventHandle::OnConnect(NetEventLoop *evloop, SocketContext *ctx)
{}

void NetEventHandle::OnMessage(NetEventLoop *evloop, SocketContext *ctx)
{}

void NetEventHandle::OnClose(NetEventLoop *evloop, SocketContext *ctx)
{}

void NetEventHandle::OnRelease(NetEventLoop *evloop, SocketContext *ctx)
{}

void NetEventHandle::OnTimer(NetEventLoop *evloop)
{}

NS_MUGGLE_END
