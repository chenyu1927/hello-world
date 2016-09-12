#include "MapStr.hpp"

int main(void)
{
	ifstream in("in.txt");
	ifstream rule("rule.txt");

	word_transform(in, rule);

	return 0;
}
