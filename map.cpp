#include<iostream>
#include<map>
#include<iomanip>
#include<string>
#include<algorithm>
#include<iterator>
using namespace std;

namespace MyLib{
	template<class Cont>
	inline
	bool replace_key(Cont& c,
					 const typename Cont::key_type& old_key,
					 const typename Cont::key_type& new_key)
	{
		typename Cont::iterator pos;
		pos = c.find(old_key);

		if (pos != c.end())
		{
			c.insert(typedef Cont::value_type(new_key, pos->second));
			c.erase(pos);
			return true;
		}
		else
		{
			return false;
		}
	}
}

//删除元素的一种方式
void delete_value(map<int, int> &coll, int value)
{
	map<int, int>::iterator iter = coll.begin();
	for (; iter != coll.end())
	{
		if (iter->second == value)
		{
			coll.erase(iter++);
		}
		else
		{
			++iter;
		}
	}
}

class RuntimeStringCmp{
	public:
		enum cmp_mode{normal, nocase};
	private:

		const cmp_mode mode;
		static bool nocase_compare(char c1, char c2)
		{
			return toupper(c1) < toupper(c2);
		}

	public:
		RuntimeStringCmp(cmp_mode m = normal) : mode(m) { }

		bool operator() (const string &s1, const string &s2) const{
			if (mode == normal)
			{
				return s1 < s2;
			}
			else
			{
				return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), nocase_compare);
			}

		}
};

typedef map<string, string, RuntimeStringCmp> StringStringMap;
int main()
{

	//set是一种特殊的map, set的操作map都支持
	
	StringStringMap coll;

}
