#ifndef THREAD_LOCAL_H_H
#define THREAD_LOCAL_H_H

#include <boost/noncopyable.hpp>
#include <pthread.h>

template <typename T>
class ThreadLocal : boost::noncopyable
{
public:
	ThreadLocal()
	{
		::pthread_key_create(&pkey_, &ThreadLocal::destructor);
	}

	~ThreadLocal()
	{
		::pthread_key_delete(pkey_);
	}

	T& value()
	{
		T* preValue = static_cast<T*>(::pthread_getspecific(pkey_));
		if (!preValue)
		{
			T* value = new T();
			::pthread_setspecific(pkey_, static_cast<const void*>(value));
			preValue = value;
		}

		return *preValue;
	}

private:

	static void destructor(void* argc)
	{
		T* value = static_cast<T*>(argc);
		delete value;
	}

	pthread_key_t pkey_;
};










#endif /* THREAD_LOCAL_H_H */
