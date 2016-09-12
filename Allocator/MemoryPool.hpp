#ifndef MEMORY_POOL_H_H
#define MEMORY_POOL_H_H

#include <stddef.h>
#include <limits.h>

template <typename T, size_t BlockSize = 4096>
class MemoryPool
{
public:
	typedef T* Ptr;

	template <typename U> struct rebind
	{
		typedef MemoryPool<U> other;
	}

	MemoryPool() noexcept
		: _currentBlock(nullptr),
		  _currentSlot(nullptr),
		  _lastBlock(nullptr),
		  _freeSlots(nullptr)
	{

	}

	~MemoryPool() noexcept
	{
		SlotPtr tmp = _currentBlock;
		while (tmp <= _lastBlock)
		{
			delete tmp;
		}
	}

	Ptr allocate(size_t n)
	{
		
	}

	template <typename U, typename... Args>
	void construct(U* p, Args&& ... args)
	{
		new (p) 
	}


	void destroy(Ptr p);

	void deallocate(Ptr p, size_t n)
	{
		if (p != nullptr)
		{
			reinterpret_cast<slotPtr>(p)->next = _freeSlots;
			_freeSlots = reinterpret_cast<slotPtr>(p);
		}
	}


private:
	union Slot_
	{
		T data;
		Slot* next;
	};

	typedef char* dataPtr;
	typedef Slot* slotPtr;

	slotPtr _currentBlock;
	slotPtr _currentSlot;
	slotPtr _lastBlock;
	slotPtr _freeSlots;
};





































#endif //MEMORY_POOL_H_H
