#include "Connector.h"
#include "EventLoop.h"
#include <iostream>

using namespace std;

int main()
{
	EventLoop baseLoop;
	InetAddress address("127.0.0.1", 8888);
	std::unique_ptr<Connector> connector(new Connector(&baseLoop, address));
	
	connector->start();

	baseLoop.loop();

	return 0;
}
