#include <list>
#include <algorithm>

class HeapTracked
{
public:
	class MissingAddress { };

	virtual ~HeapTracked() = 0;

	static void* operator new(size_t size);
	static void operator delete(void* ptr);

	bool isOnHeap();

private:
	typedef const void* RawAddress;
	static std::list<RawAddress> address_;
};

std::list<HeapTracked::RawAddress> HeapTracked::address_;

HeapTracked::~HeapTracked()
{/* NULL */ }

void* HeapTracked::operator new(size_t size)
{
	void* memPtr = ::operator new(size);
	if (memPtr)
	{
		address_.push_front(memPtr);
	}

	return memPtr;
}

void HeapTracked::operator delete(void* ptr)
{
	std::list<RawAddress>::iterator iter = std::find(address_.begin(), address_.end(), ptr);
	if (iter != address_.end())
	{
		address_.erase(iter);
		::operator delete(ptr);
	}
	else
	{
		throw MissingAddress();
	}
}

bool HeapTracked::isOnHeap()
{
	const void* memPtr = dynamic_cast<const void*>(this);
	return std::find(address_.begin(), address_.end(), memPtr) != address_.end();
}

