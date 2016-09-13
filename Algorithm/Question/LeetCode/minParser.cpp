#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class ValueT
{
public:

	ValueT()
		: n_(0)
	{}

	ValueT(int n)
		: n_(n)
	{}

	int n() const { return n_; }
	void set_n(int n) { n_ = n; }

private:
	int n_;
};


class NestedInteger
{
public:
	enum{
		ELEM_NONE = 0,
		ELEM_SINGLE = 1,
		ELEM_LIST = 2
	};

	NestedInteger()
		:flag_(ELEM_NONE)
	{ }

	NestedInteger(int flag)
		: flag_(flag)
	{
		if (flag_ == ELEM_LIST)
			list_ = make_shared<vector<ValueT>>();
		else if (flag_ == ELEM_SINGLE)
			nt = make_shared<ValueT>();
	}

	~NestedInteger()
	{

	}

	bool isInteger() { return flag_ == ELEM_SINGLE; }

	int getValue() const { return nt->n(); }
	void setValue(int n) { nt->set_n(n); }
	void addInterger(const ValueT& nt)
	{
		list_->push_back(nt);
	}
	vector<ValueT>& getIntegerList()
	{
		return *list_;
	}

private:

	typedef vector<ValueT> List;

	int flag_;  //if is int or list
	union {
		shared_ptr<ValueT> nt;
		shared_ptr<List> list_;
	};
//	vector<NestedInteger> list_;
};

NestedInteger parser(string s)
{
	if (s.front() == '[')
	{
		NestedInteger list(NestedInteger::ELEM_LIST);
		size_t ppos = 1;
		while (ppos != string::npos)
		{
			auto pos = s.find_first_of(',', ppos);
			string temp(s, ppos, pos -1);
			ValueT value(stoi(temp));
			list.addInterger(value);

			ppos = pos+1;
		}
	}
	else
	{
		//auto pos = s.find_first_of(',');
		
		//string temp(s.c_str(), pos-1);
		NestedInteger value(NestedInteger::ELEM_SINGLE);
		int n = stoi(s);
		cout << "n = " << n << endl;
		value.setValue(n);
		return value;
	}
}

int main()
{
	string s = "234";
	NestedInteger value = parser(s);

	cout << "value " << value.getValue() << endl;

	return 0;
}
