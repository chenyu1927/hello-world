#include "HttpServer.h"
#include <memory>
#include "EventLoop.h"
#include "InetAddress.h"

int main()
{
	EventLoop baseLoop;
	InetAddress serverAddr(8888);
	std::unique_ptr<HttpServer> hs(new HttpServer(&baseLoop, serverAddr, "HttpServer"));
	
	hs->start();

	baseLoop.loop();

	return 0;
}
