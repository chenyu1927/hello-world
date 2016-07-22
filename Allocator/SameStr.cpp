#include <string>

using namespace std;

class SameStr
{
	friend void swap(SameStr&, SameStr&);
public:
	SameStr(const string& str);
	SameStr(const SameStr& other);
	
	SameStr& operator=(const SameStr& other);

	~SameStr();

private:
	string* str_;
	int i;
};

SameStr::SameStr(const string& str)
	: str_(new string(str)),
	  i(0)
{

}

SameStr::SameStr(const SameStr& other)
	: str_(new string(*other.str_)),
	  i(other.i)
{

}

SameStr& SameStr::operator=(const SameStr& other)
{
//	auto temp = new string(*other.str_);
	string* temp = new string(*other.str_);	
	delete str_;

	str_ = temp;
	i = other.i;
	return *this;
}

SameStr::~SameStr()
{
	if (str_)
		delete str_;
}


inline void swap(SameStr& lhs, SameStr& rhs)
{
	std::swap(lhs.str_, rhs.str_);
	std::swap(lhs.i, rhs.i);
}
///////////////////////////////////////////////////////////////////////
class SmartPtr
{
public:
	explicit SmartPtr(const string& str) /*explicit*/
		: str_(new string(str)),
		  i(0),
		  count_(new int(1))
	{

	}

	SmartPtr(const SmartPtr& other)
		: str_(other.str_),
		  i(other.i),
		  count_(other.count_)
	{
		++ (*count_);
	}

	SmartPtr& operator=(const SmartPtr& other)
	{
		if (this == &other)
			return *this;

		-- (*count_);
		if (*count_ == 0)
		{
			delete str_;
			delete count_;
		}

		str_ = other.str_;
		i = other.i;
		count_ = other.count_;
		++ (*count_);

		return *this;
	}

	~SmartPtr()
	{
		if (-- (*count_) == 0)
		{
			delete count_;
			delete str_;
		}
	}

private:
	string* str_;
	int i;
	int* count_;
};

int main(void)
{
	SameStr sstr("hello world");
	SameStr ssstr("chen yu");

	ssstr = sstr;

	string str("chenyu");
	SmartPtr sptr(str);

	SmartPtr ssptr = sptr;
	
	{
		string sstr;
		SmartPtr sssptr(sstr);
		sssptr = sptr;
	}

	return 0;
}
