#ifndef REFOBJECT_H_H
#define REFOBJECT_H_H

#include "MutexLock.hpp"

class RefObject
{
public:
	RefObject();
	virtual ~RefObject();
	void AddRef(void);
	void ReleaseRef(void);
	void set_lock(MutexLock *lock)
	{
		mutex_ = lock;
	}
private:
	int refCounts_;
	MutexLock *mutex_;
};


#endif /* REFOBJECT_H_H */
