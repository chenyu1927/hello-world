#include "TcpServer.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include <stdio.h>
#include "Type.h"
#include "Buffer.h"
#include "TcpConnection.h"

void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{
	std::string data = buf->retrieveAllAsString();
	fprintf(stdout, "tcp server recv data %s\n", data.c_str());
	conn->send(std::move(data));
}

int main()
{
	EventLoop baseLoop;
	InetAddress listenAddr("127.0.0.1", 8888);
	std::unique_ptr<TcpServer> tcpServer(new TcpServer(&baseLoop, listenAddr, "test"));
	tcpServer->setMessageCallback(std::move(onMessage));
	tcpServer->start();

	baseLoop.loop();

	return 0;
}
