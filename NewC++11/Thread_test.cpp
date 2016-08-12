#include "Thread.h"
#include "CurrentThread.h"
#include <iostream>

using namespace std;

void func()
{
	auto i = 10;
	while (i > 0)
	{
		cout << static_cast<char>('a' + i) << " ";
		--i;
	}

	cout << CurrentThread::name() << " " << CurrentThread::tid() << CurrentThread::isMainThread() << endl;
}

int main()
{
	Thread thread([] {auto i = 10; while (i > 0)
			cout << i-- << " "; cout << CurrentThread::name() << endl;});
	cout << CurrentThread::name() << endl;
	
	Thread thread1(func);


	thread.start();
	thread1.start();

	thread1.join();
	thread.join();

	return 0;
}
