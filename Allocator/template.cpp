#include <iostream>
#include <cstring>

using namespace std;


template <typename T>
inline T self_max(const T x, const T y)
{
	return x > y ? x : y;
}

template <unsigned N, unsigned M>
inline int compare(const char (&p1)[N], const char (&p2)[M])
{
	return strcmp(p1, p2);
}


template <typename To, typename From>
inline To implicit_cast(const From& from)
{
	return from;
}

template <typename To, typename From>
inline To down_cast(From* f) // use like down_cast<To*>(this);
{
	if (false)
		implicit_cast<To, From*>(0);

	return static_cast<To>(f);
}

int main(void)
{
	cout << self_max(10, 19) << endl;
	cout << compare("chen", "yu");
	return 0;
}
