#include <iostream>
#include <string>
#include <assert.h>
#include <cstring>
using namespace std;

void strReverse(char *src)
{
	assert(src);
	int len = static_cast<int>(strlen(src));
	len = len - 1;
	for (int i = 0; i < len; ++ i, -- len)
	{
		std::swap(src[i], src[len]);
	}
}

int main(void)
{
	string str("hello");
//	cout << str << ' ' << str.reverse() << endl;

	char buf[] = "chenyu";
	cout << buf << endl;
	strReverse(buf);
	cout << buf << endl;

	return 0;
}
