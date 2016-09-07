#include "Connector.h"
#include "EventLoop.h"
#include "SocketOps.h"
#include "TcpConnection.h"
#include "Type.h"
#include <iostream>

using namespace std;

int main()
{
	EventLoop baseLoop;
	InetAddress address("127.0.0.1", 8888);
	std::shared_ptr<Connector> connector(new Connector(&baseLoop, address));
	
	TcpConnectionPtr tcpConnPtr;

	connector->setNewConnectionCallback([&](int sockfd) {
						InetAddress peerAddr(sockets::getPeerAddr(sockfd));
						tcpConnPtr.reset(new TcpConnection(&baseLoop, "connection one", 
								sockfd, peerAddr, address));
						tcpConnPtr->setConnectionCallback(defaultConnectionCallback);
						tcpConnPtr->setMessageCallback(defaultMessageCallback);
						tcpConnPtr->send("what is your name?");
			});

	connector->start();
	
	baseLoop.loop();

	return 0;
}
