#ifndef CURRENT_THREAD_H_H
#define CURRENT_THREAD_H_H

#include <stdint.h>

namespace CurrentThread
{
	extern __thread int t_cacheTid; //__thread can not destruction, so use pthread_key_t replace!
	extern __thread const char* t_threadName;

	void cacheTid();
	
	inline int tid()
	{
		if (__builtin_expect(t_cacheTid == 0, 0))
		{
			cacheTid();
		}

		return t_cacheTid;
	}

	inline const char* name() { return t_threadName; }

	bool isMainThread();
	void sleepUsec(int64_t usec);
}



#endif /* CURRENT_THREAD_H_H */
