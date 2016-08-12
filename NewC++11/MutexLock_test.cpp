//#include "MutexLock.h"
#include "Condition.h"

int main()
{
	MutexLock lock;
	MUTEX_GUARD(lock, Obj);
	Condition cond(lock);
	lock.assertLocked();

	cond.wait();

	return 0;
}
