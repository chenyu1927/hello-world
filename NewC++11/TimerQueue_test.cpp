#include "TimerQueue.h"
#include "EventLoop.h"

#include <iostream>

using namespace std;

void timeOut()
{
	cout << "time out " << endl;
}

void doAfter()
{
	cout << "do after " << endl;
}

int main()
{
	EventLoop baseLoop;
	
	baseLoop.runEvery(2, timeOut);
	baseLoop.runAfter(10, doAfter);
	

	baseLoop.loop();

	return 0;
}
