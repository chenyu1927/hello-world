#include "EventLoopThreadPool.h"
#include "EventLoopThread.h"
#include "EventLoop.h"
#include "CurrentThread.h"
#include <iostream>
using namespace std;

void func()
{
	int i = 4;
	while (--i >= 0)
	{
		cout << "loop 1 cout << " << i << endl;
	}

	cout << CurrentThread::t_threadName << ' '  << CurrentThread::t_cacheTid << endl;
}


int main()
{
	EventLoop baseLoop;
	EventLoopThreadPool loop_pool(&baseLoop, "ChenYu");
	loop_pool.setNumThreads(3);
	loop_pool.start();
	loop_pool.getNextLoop()->runInLoop([] { int i =4; while (--i >= 0)cout << "hello world!" << endl; });
	loop_pool.getNextLoop()->runInLoop(func);
	baseLoop.loop();

	return 0;
}
