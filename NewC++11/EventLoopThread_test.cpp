#include "EventLoopThread.h"
#include "EventLoop.h"
#include <iostream>
using namespace std;

int main()
{
	EventLoopThread thr_loop;
	EventLoop* loop = thr_loop.startLoop();
	loop->queueInLoop([] { int i = 5; while (i > 0) cout << i-- << endl;});
	EventLoop event_loop;
	event_loop.loop();
	return 0;
}
