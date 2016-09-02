#include "TimerQueue.h"
#include "EventLoop.h"

#include <iostream>

using namespace std;

void timeOut()
{
	cout << "time out " << endl;
}

int main()
{
	EventLoop baseLoop;
	
	baseLoop.runEvery(2, timeOut);

	baseLoop.loop();

	return 0;
}
