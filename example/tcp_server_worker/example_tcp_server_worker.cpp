#include "muggle/cpp/muggle_cpp.h"
#include <vector>
#include <thread>
#include "struct.h"
#include "tcp_listen_handle.h"
#include "tcp_worker_handle.h"

USING_NS_MUGGLE;

void run_tcp_server(const char *host, const char *serv)
{
	std::vector<NetEventLoop*> worker_evloops;
	for (int i = 0; i < 8; i++)
	{
		NetEventLoop *worker_evloop = new NetEventLoop(512, 0);
		TCPWorkerHandle *worker_handle = new TCPWorkerHandle();
		worker_handle->SetWorkerId(i);
		worker_evloop->SetHandle(worker_handle);
		worker_evloops.push_back(worker_evloop);
		std::thread th([worker_evloop]{
			worker_evloop->Run();
		});
		th.detach();
	}

	NetEventLoop listen_evloop(512, 0);

	TCPListenHandle listen_handle;
	listen_handle.SetWorkers(&worker_evloops);
	listen_evloop.SetHandle(&listen_handle);

	SocketContext *listen_ctx = SocketUtils::TCPListen(host, serv, 512);
	listen_evloop.AddContext(listen_ctx);

	listen_evloop.Run();

	// for (NetEventLoop *worker_evloop : worker_evloops)
	// {
	// 	delete worker_evloop->GetHandle();
	// 	delete worker_evloop;
	// }
	// worker_evloops.clear();
}

int main (int argc, char *argv[])
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

	run_tcp_server(host, serv);
	
	return 0;
}
