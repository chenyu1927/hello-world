#ifndef SINGLETON_H_H
#define SINGLETON_H_H
#include <boost/noncopyable.hpp>

template<typename T>
class Singleton : boost::noncopyable
{
public:
	static T* instance();
	void destory();
private:
	Singleton();
	~Singleton();
	
private:
	static Singleton* instance_;
	T	obj_;
};

template<class T>
Singleton<T>::Singleton()
{

}

template<class T>
Singleton<T>::~Singleton()
{

}

template<class T>
T* Singleton<T>::instance()
{
	if (Singleton<T>::instance_ == 0)
		Singleton<T>::instance_ = new Singleton;
	return &(Singleton<T>::instance_->obj_);
}

template<class T>
void Singleton<T>::destroy()
{
	if (Singleton<T>::instance_ != 0)
		delete Singleton<T>::instance_;

}

template<class T>
T& instance(void)
{
	static T obj;
	return obj;
}


#endif /* SINGLETON_H_H */
