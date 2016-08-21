#include "Acceptor.h"
#include "EventLoopThread.h"
#include "EventLoopThreadPool.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include <memory>

int main()
{
/*	EventLoop loop;
	InetAddress localaddr("127.0.0.1", 8888);
	std::unique_ptr<Acceptor> accept(new Acceptor(&loop, localaddr));
	accept->listen();
	loop.loop();*/

	EventLoopThread thread([](EventLoop* loop) {
								InetAddress localaddr("127.0.0.1", 8888);
								Acceptor accept(loop, localaddr); //这个对象是临时的
								accept.listen();
			}, "Acceptor");

	EventLoop* acceptLoop = thread.startLoop();
	
	EventLoop baseLoop;
	baseLoop.loop();

/*	EventLoop baseLoop;
	InetAddress localaddr("127.0.0.1", 8888);
	Acceptor acceptor(&baseLoop, localaddr);
	acceptor.listen();
	baseLoop.loop();*/
//	EventLoopThreadPool pool(&baseLoop);
	

	return 0;
}
