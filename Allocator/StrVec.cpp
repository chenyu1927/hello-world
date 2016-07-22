#include <memory>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class StrVec
{
public:
	StrVec()
		: element_(0),
		  free_(0),
		  cap_(0)
	{ }

	StrVec(const StrVec& other);
	StrVec& operator=(const StrVec& other);

	~StrVec();

	void push_back(const string&);
	size_t size() const { return free_ - element_; }
	size_t capacity() const { return cap_ - element_; }
	
	string* begin() const { return element_; }
	string* end() const { return free_; }

private:
	void chk_n_alloc();
	pair<string*, string*> alloc_n_copy(string* e, string* c);
	void free();
	void reallocate();

private:
	static allocator<string> alloc_;

	string* element_;
	string* free_;
	string* cap_;
};

allocator<string> StrVec::alloc_;

void StrVec::push_back(const string& other)
{
	chk_n_alloc();
	alloc_.construct(free_++, other);
}

void StrVec::chk_n_alloc()
{
	if (size() == capacity())
		reallocate();
}

pair<string*, string*> StrVec::alloc_n_copy(string* b, string* e)
{
	string* data = alloc_.allocate(e - b);
//	return {data, uninitialized_copy(b, e, data)};
	return make_pair(data, uninitialized_copy(b, e, data));
}

void StrVec::free()
{
	if (element_)
	{
/*		while (free_ != element_)
			alloc_.destroy(--free_);*/
		for_each(element_, free_, [] (string& p) -> void  { alloc_.destroy(&p); });
		alloc_.deallocate(element_, cap_ - element_);
	}
}

/*void StrVec::reallocate()
{
//	if (capacity() <= 0)
//	{		
//		element_ = alloc_.allocate(1);
//		cap_ = element_ + 1;
//		free_ = element_;
//	}
//	else
	{
		size_t newCap = size() > 0 ? size() * 2 : 1;
		string* new_element = alloc_.allocate(newCap);
		string* new_free = uninitialized_copy(element_, free_, new_element);
	
		free();

		cap_ = new_element + newCap;
		element_ = new_element;
		free_ = new_free;
	 }
}*/

//#ifdef C++11
void StrVec::reallocate()
{
	size_t newCapacity = size() > 0 ? size() * 2 : 1;
	string* n_element = alloc_.allocate(newCapacity);
	string* q = n_element;
	for (string* pos = element_; pos != free_; ++ pos)
	{
		alloc_.construct(q++, std::move(*pos));
	}

	free();

	cap_ = n_element + newCapacity;
	element_ = n_element;
	free_ = q;
}

//#endif

StrVec::StrVec(const StrVec& other)
{
//	element_ = alloc_.allocate(other.size());
//	free_ = uninitialized_copy(other.element_, other.free_, element_);
	pair<string*, string*> iter = alloc_n_copy(other.element_, other.free_);
	element_ = iter.first;
	cap_ = free_ = iter.second;
}

StrVec& StrVec::operator= (const StrVec& other)
{
	if (this == &other)
		return *this;

	free();

	element_ = alloc_.allocate(other.size());
	free_ = uninitialized_copy(other.element_, other.free_, element_);
	cap_ = element_ + other.size();
	return *this;
}

StrVec::~StrVec()
{
	free();
}

int main(void)
{
	StrVec str_vec;
	
	string str1("hello world!");
	string str2("chenyu");

	str_vec.push_back(str1);
	str_vec.push_back(str2);

	for(string* x = str_vec.begin(); x != str_vec.end(); ++ x)
	{
		cout << *x << endl;
	}
	
	StrVec str_vec2 = str_vec;

	for(string* x = str_vec2.begin(); x != str_vec2.end(); ++ x)
	{
		cout << *x << endl;
	}
	return 0;
}
