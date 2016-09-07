#include "TcpClient.h"
#include "EventLoop.h"
#include <memory>
#include "InetAddress.h"


int main()
{
	EventLoop baseLoop;
	InetAddress serverAddr("127.0.0.1", 8888);
	std::shared_ptr<TcpClient> tcpClient(new TcpClient(&baseLoop, serverAddr, "test"));
	tcpClient->connect();
	
//	std::unique_ptr<Thread> thread(new Thread([]))

	baseLoop.loop();
	return 0;
}
