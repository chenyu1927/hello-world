#include <vector>
#include <iostream>

using namespace std;

template <typename NodeType>
class StaticListNode
{
public:
	const static int null_ptr = -1;

	StaticListNode()
		: idx_(null_ptr),
		  prev_(null_ptr),
		  next_(null_ptr),
		  is_used_(false)
	{

	}

	void reset()
	{
		idx_ = null_ptr;
		prev_ = null_ptr;
		next_ = null_ptr;

		is_used_ = false;
	}

	int idx_;
	int prev_;
	int next_;

	bool is_used_;
	NodeType node_;
};

template <typename NodeType>
class StaticList
{
public:
	typedef StaticListNode<NodeType> Node;
	const static int kFreeHeadIdx = 0;
	const static int kUsedHeadIdx = 1;

public:
	StaticList()
	{
		init();
	}

	~StaticList()
	{
		fini();
	}

	int push(NodeType x)
	{
		int idx = -1;

		if (freeHead().prev_ == kFreeHeadIdx && freeHead().next_ == kFreeHeadIdx)
		{ //空空闲链表
			Node node;
			node.node_ = x;
			node.idx_ = static_cast<int>(node_list_.size());
			node.prev_ = kFreeHeadIdx;
			node.is_used_ = true;

			node.next_ = usedHead().next_;
			node_list_[usedHead().next_].prev_ = node.idx_;
			usedHead().next_ = node.idx_;

			node_list_.push_back(node);
			idx = node.idx_;
		}
		else
		{
			Node& free_node = node_list_[freeHead().next_];
			node_list_[free_node.next_].prev_ = kFreeHeadIdx;
//			node_list_[free_node.prev_].next_ = free_node.next_;
			freeHead().next_ = free_node.next_;

			free_node.prev_ = kUsedHeadIdx;
			free_node.next_ = usedHead().next_;

			node_list_[usedHead().next_].prev_ = free_node.idx_;
			usedHead().next_ = free_node.idx_;

			free_node.is_used_ = true;
			free_node.node_ = x;

			idx = free_node.idx_;
			
		}

		return idx;
	}

	//删除idx，添加到空闲链表尾
	int pop(int idx)
	{
		if (!validate_id(idx))
			return -1;

		Node& node = node_list_[idx];
		if (!node.is_used_)
			return -1;

		node_list_[node.prev_].next_ = node.next_;
		node_list_[node.next_].prev_ = node.prev_;

		node.prev_ = freeHead().prev_;
		node.next_ = kFreeHeadIdx;

		node_list_[freeHead().prev_].next_ = node.idx_;
		freeHead().prev_ = node.idx_;

		if (freeHead().next_ == kFreeHeadIdx)
		{
			freeHead().next_ = node.idx_;
		}

		node.is_used_ = false;
		
		return 0;
	}

private:

	bool validate_id(int idx)
	{
		if (idx < 2 || idx > static_cast<int>(node_list_.size()))
			return false;
		return true;
	}

	Node& freeHead()
	{ return node_list_[kFreeHeadIdx]; }

	Node& usedHead()
	{ return node_list_[kUsedHeadIdx]; }

	void init()
	{
		node_list_.clear();

		Node node;
		node.idx_ = kFreeHeadIdx;
		node.prev_ = node.next_ = kFreeHeadIdx;
		node.is_used_ = true;

		node_list_.push_back(node);

		node.reset();
		node.idx_ = kUsedHeadIdx;
		node.prev_ = node.next_ = kUsedHeadIdx;
		node.is_used_ = true;

		node_list_.push_back(node);
	}

	void fini()
	{
		node_list_.clear();
	}

private:
	vector<Node> node_list_;
};

int main(void)
{
	StaticList<int> static_list;

	int id = static_list.push(56);

	cout << id << endl;
	cout << static_list.pop(id) << endl;

	id = static_list.push(60);
	cout << id << endl;
	return 0;
}
