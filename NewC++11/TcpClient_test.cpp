#include "TcpClient.h"
#include "TcpConnection.h"
#include "EventLoop.h"
#include <memory>
#include "InetAddress.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <vector>
#include "Buffer.h"
#include "Thread.h"
#include <strings.h>

void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{
	std::string data = buf->retrieveAllAsString();
	fprintf(stdout, "%s \n", data.c_str());
}

int main()
{
	EventLoop* baseLoop = new EventLoop;;
	InetAddress serverAddr("127.0.0.1", 8888);
	std::shared_ptr<TcpClient> tcpClient(new TcpClient(baseLoop, serverAddr, "test"));
	tcpClient->connect();
	
	std::unique_ptr<Thread> thread(new Thread([=] {
					char buf[64];
					while (true) {
						bzero(buf, sizeof buf);
						char* tmp = buf;
						gets(tmp);
						tcpClient->connection()->send(buf);
					}
				}));
	
	thread->start();
	baseLoop->loop();

	thread->join();
	return 0;
}
