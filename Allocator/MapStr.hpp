#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <memory>
#include <iostream>

using namespace std;

string kDefaultRuleFile("rule.txt");

typedef shared_ptr<map<string, string>> MapPtr;

MapPtr load_rule(ifstream& rule)
{
	if (!rule.is_open())
		rule.open(kDefaultRuleFile);

	MapPtr rulePtr= make_shared<map<string, string>>();
	string key;
	string value;
	while (rule >> key && getline(rule, value))
	{
		rulePtr->insert(make_pair(key, value));
	}
	//for (string line; getline(rule, line); )
	//{
	//	istringstream iss(line);
	//	string key;
	//	iss >> key;
	//	rulePtr->insert(make_pair(key, iss.str()));
	//}

	return rulePtr;
}

string transform(const string& src, MapPtr& rule)
{
	auto des = rule->find(src);
	if (des != rule->end())
	{
		return des->second;
	}
	else
		return src;
}

void word_transform(ifstream& in, ifstream& rule)
{
	auto rulePtr = load_rule(rule);

	for (string line; getline(in, line); )
	{
		istringstream iss(line);
		bool first_world = false;
		for (string elem; iss >> elem; )
		{
			if (!first_world)
				first_world = true;
			else
				cout << " "; 
			cout << transform(elem, rulePtr);
		}
		cout << endl;
	}
}
