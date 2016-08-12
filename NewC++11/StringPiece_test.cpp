#include "StringPiece.h"
#include <iostream>

using namespace std;

int main(void)
{
	StringPiece str("chenyu_test");

	cout << str.size() << endl;

	string s;
	str.copyToString(&s);
	cout << s << endl;
	return 0;
}
