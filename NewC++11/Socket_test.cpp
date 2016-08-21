#include "Socket.h"
#include "InetAddress.h"
#include "SocketOps.h"
#include <memory>
#include "Channel.h"
#include "EventLoopThread.h"
#include "EventLoop.h"

#include <iostream>
using namespace std;

int main()
{
	EventLoopThread thread;
	EventLoop* loop = thread.startLoop();
//	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int sockfd = sockets::createNonblockingOrDie(AF_INET);
	unique_ptr<Socket> psock(new Socket(sockfd));
	InetAddress address("127.0.0.1", 8888);
	
	psock->bindAddress(address);
	psock->listen();

	Channel channel(loop, sockfd);
	channel.setReadCallback([&](Timestamp time) { psock->accept(nullptr); });
	channel.enableReading();

	EventLoop baseLoop;
	baseLoop.loop();

	return 0;

}
