#include <new>

template <typename T>
class self_shared_ptr
{
public:
	self_shared_ptr(T* p) throw()
		: _pointer(p),
		  _count(new (std::nothrow) long(1))
	{

	}

	self_shared_ptr(const self_shared_ptr<T>& other)
		: _pointer(other._pointer), _count(other._count)
	{
//		swap(other);
//		_pointer = other._pointer;
//		_count = other._count;
		++ *_count;
	}

	self_shared_ptr& operator=(const self_shared_ptr& other)
	{
		if (this == &other)
			return *this;

		_dispost();
		_pointer = other._pointer;
		_count = other._count;
		++ *_count;
		return *this;
	}

	T& operator*() const
	{
		return *_pointer;
	}

	T* operator->() const
	{
		return _pointer;
	}

	//隐式转换
	operator void*() // FIXME::可以使用，但是会将很多类型转换为void*。
	{
		if (_pointer == nullptr)
			return 0;
		else
	//		return _pointer;
			return static_cast<void*>(_pointer);
	}

	operator bool() //FIXME::标准库采用这种形式来完善前一版本的问题！
	{
		return _pointer != nullptr;
	}

	bool operator !() const
	{
		return _pointer == nullptr;
	}

	operator T*() const //FIXME::此法并不是很好,有危险，例如: self_shared_ptr<xx> obj; delete obj;能通过
	{
		return _pointer;
	}

	template <typename NewType>
	operator self_shared_ptr<NewType>() //为支持多态，提供的类型转换, NewType 和T存在继承关系
	{
		return self_shared_ptr<NewType>(_pointer);
	}

private:
	void _dispost()
	{
		if (-- *_count == 0)
		{
			delete _pointer;
			delete _count;

			_pointer = nullptr;
			_count = nullptr;
		}
	}

private:
	T* _pointer;
	long* _count;
};
