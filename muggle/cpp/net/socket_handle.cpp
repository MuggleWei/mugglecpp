#include "socket_handle.h"

NS_MUGGLE_BEGIN

SocketHandle::SocketHandle()
{}

SocketHandle::~SocketHandle()
{}

void SocketHandle::onBind(muggle_socket_event_t*, SocketPeer*)
{}

void SocketHandle::onListen(muggle_socket_event_t*, SocketPeer*)
{}

void SocketHandle::onConnect(muggle_socket_event_t*, SocketPeer*)
{}

void SocketHandle::onError(muggle_socket_event_t*, SocketPeer*)
{}

void SocketHandle::onMessage(muggle_socket_event_t*, SocketPeer*)
{}

void SocketHandle::onTimer(muggle_socket_event_t*)
{}

void SocketHandle::onClose(muggle_socket_event_t*, SocketPeer*)
{}

NS_MUGGLE_END
