#include "MsgTable.hpp"
#include <memory>

int main()
{
	unique_ptr<Monitor> monitor(new Monitor);
	int i;
	cin >> i;
	monitor->dispatch(i);
	return 0;
}
