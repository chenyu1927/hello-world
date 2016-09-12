#include <memory>
#include <iostream>
using namespace std;

template <typename T>
struct StackNode
{
	T __data;
	StackNode* __prev;
};

template <typename T, typename Alloc = std::allocator<T> >
class StackAlloc
{
public:
	typedef StackNode<T> Node;
	typedef typename Alloc::template rebind<Node>::other Allocator; //FIXME: need to learn rebind

	StackAlloc()
		: head_(nullptr)
	{}

	~StackAlloc()
	{
		clear();
	}

	bool empty() const { return head_ == nullptr; }

	T pop()
	{
		T data = head_->__data;
		Node* tmp = head_->__prev;
		alloc_.destroy(head_);
		alloc_.deallocate(head_, 1);
		head_ = tmp;
		return data;

	}
	void push(T data)
	{
		Node* tmp = alloc_.allocate(1);
		alloc_.construct(tmp, Node());
		tmp->__data = data;
		tmp->__prev = head_;
		head_ = tmp;

	}

	void clear()
	{

		while (head_)
		{
			auto tmp = head_->__prev;
			alloc_.destroy(head_);
			alloc_.deallocate(head_, 1);
			head_ = tmp;
		}
	}


private:
	Node* head_;
	Allocator alloc_;
};

/*template <typename T, typename Alloc>
T StackAlloc<T, Alloc>::pop()
{
	T data = head_->__data;
	Node* tmp = head_->__prev;
	alloc_.destory(head_);
	alloc_.dealloctor(head_, 1);
	head_ = tmp;
	return data;
}

template <typename T, typename Alloc>
void StackAlloc<T, Alloc>::push(T data)
{
	Node* tmp = alloc_.allocate(1);
	alloc_.construct(tmp, Node());
	tmp->__data = data;
	tmp->__data = head_;
	head_ = tmp;
}

template <typename T, typename Alloc>
void StackAlloc<T, Alloc>::clear()
{
	while (head_)
	{
		auto tmp = head_->__prev;
		alloc_.destroy(head_);
		alloc_.dealloctor(head_, 1);
		head_ = tmp;
	}
}*/

int main()
{
	StackAlloc<int> stack;
	stack.push(5);
	cout << "pop stack alloctor " << stack.pop() << endl;
	return 0;
}
