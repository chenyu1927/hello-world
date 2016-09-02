#include "TcpServer.h"
#include "Acceptor.h"
#include "EventLoopThreadPool.h"
#include "EventLoop.h"


TcpServer::TcpServer(EventLoop* loop, const InetAddress& address, const std::string& nameArg, Option opt)
	: loop_(loop), ipPort_(address.toIpPort()), name_(nameArg), acceptor_(new Acceptor(loop_, address, opt)),
	  threadPool_(new EventLoopThreadPool(loop_, nameArg)), started_(false), nextConnId_(1)
{

}

TcpServer::~TcpServer()
{
	for (auto iter : connections_)
	{

	}
}


