#include "FileUntil.h"
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	fileUntil::ReadSmallFile sreader("Thread.h");
	int size = 0;
	sreader.readToBuffer(&size);
	cout << "file size = " << size << endl;
	cout << sreader.buffer() << endl;

	string str;
	int64_t fileSize = 0;
	int64_t ct = 0;
	int64_t mt = 0;
	fileUntil::readFile("Thread.h", 3024, &str, &fileSize, &ct, &mt);

	cout << str << endl;
	cout << "size = " << fileSize << "creat time = " << ct << "modify time = " << mt << endl;
	return 0;
}
