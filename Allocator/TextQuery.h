#ifndef TEXT_QUERY_H_H
#define TEXT_QUERY_H_H

#include <memory>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <fstream>
#include <iostream>
//#include <stdio.h>

using namespace std;

class TextQuery
{
public:
	typedef set<int> LineNums;

public:
	TextQuery(const string& filepath)
	{
		loadFile(filepath);
	}

	~TextQuery()
	{ }
	
	void loadFile(const string& filepath);
//	QueryResult* search(const string& element);
	void printLine()
	{
		auto iter = lines_.begin();
		for (; iter < lines_.end(); ++iter)
		{
			cout << *iter << endl;
		}
	}

	void printElement()
	{
		auto iter = text_map_.begin();
		for (; iter != text_map_.end(); ++ iter)
		{
			cout << iter->first << endl;
		}
	}
	
	LineNums* lineList(const string& element)
	{
		auto iter = text_map_.find(element);
		if (iter != text_map_.end())
			return &(iter->second);
		else
			return 0;
	}

	vector<string>& text()
	{ return lines_; }

private:

	vector<string> lines_;
	map<string, LineNums> text_map_;
};

void TextQuery::loadFile(const string& filepath)
{
//	FILE* fp = fopen(filepath.c_str(), "r");
//	if (!fp)
//	{
//		return ;
//	}
	
	ifstream in(filepath);
//	in.open();
	if (!in.is_open())
		return ;
	
	int lineNum = 0;
	for (string line; getline(in, line); )
	{
		++ lineNum;
		lines_.push_back(line);

		istringstream record(line);
		for (string element; record >> element; )
		{
			text_map_[element].insert(lineNum);
		}

	}
//	vector<char> buf;
//	buf.resize(256);

/*	int lineNum = 0;
	while ((char* s = fgets(buf.begin(), buf.size(), fp)) != 0)
	{
		++ lineNum;
		string str(s);
		vector.push_back(str);

		istringstream record(str);
		string element;

		while (record >> element)
		{
			LineNums& lineNums = text_map_[element];
			lineNums.insert(lineNum);

			element.clear();
		}
	}*/
}

////////////////////////////////////////////////////////////////////////////////////
class QueryResult
{
public:
	QueryResult(const string& file)
		: cursor_(new TextQuery(file))
	{

	}

	void runSearch(istream& in);

private:
	shared_ptr<TextQuery> cursor_;
};

void QueryResult::runSearch(istream& in)
{
	string element;
	in >> element;

	TextQuery::LineNums* lines = cursor_->lineList(element);
	if (lines)
	{
		for (auto iter = lines->begin(); iter != lines->end(); ++ iter)
		{
			cout << *iter << ' ' << cursor_->text()[*iter - 1] << endl;
		}
	}
}




#endif /* TEXT_QUERY_H_H */
