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

RefObject::RefObject()
{
	mutex_ = 0;
	refCounts_ = 1;
}

void RefObject::AddRef()
{
	if (mutex_)
	{
		MUTEX_GUARD(obj, *mutex_);
		refCounts_ += 1;
	}
	else
		refCounts_ += 1;
}

void RefObject::ReleaseRef()
{
	if (mutex_)
	{
		MUTEX_GUARD(obj, *mutex_);
		refCounts_ -= 1;
		if (refCounts_ <= 0)
			delete this;
	}
	else
	{
		refCounts_ -= 1;
		if (refCounts_ <= 0)
			delete this;
	}
}

RefCount::~RefCount()
{
	mutex_ = 0;
}

#endif /* REFOBJECT_H_H */
