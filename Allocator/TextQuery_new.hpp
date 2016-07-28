#ifndef TEXT_QUERY_NEW_H_H
#define TEXT_QUERY_NEW_H_H

#include <memory>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class QueryResult;

class TextQuery
{
public:
	using line_n = vector<string>::size_type;

public:
	TextQuery(ifstream& in);
	QueryResult runSearch(const string& str) const;

private:
	void loadFile(ifstream& in);

private:
	shared_ptr<vector<string> > text_;
	map<string, shared_ptr<set<line_n>>> text_map_;
};

TextQuery::TextQuery(ifstream& in)
{
	text_ = make_shared<vector<string>>();
	loadFile(in);
}

void TextQuery::loadFile(ifstream& in)
{
	if (in.is_open())
	{
		for (string line; getline(in, line); )
		{
			text_->push_back(line);
			line_n n = text_->size() - 1;
			
			istringstream elements(line);
			string element;
			while (elements >> element)
			{
				auto &line_s = text_map_[element];
				if (!line_s)
					line_s.reset(new set<line_n>);
				line_s->insert(n);
			}
		}
	}
}

/*QueryResult TextQuery::runSearch(const string& str) const
{
	static shared_ptr<set<line_n>> nodata = make_shared<set<line_n>>();
	auto iter = text_map_.find(str);
	if (iter != text_map_.end())
		return QueryResult(str, iter->second, text_);
	else
		return QueryResult(str, nodata, text_);

}*/

class QueryResult
{
public:
	QueryResult(const string& key, const shared_ptr<set<TextQuery::line_n>>& lines, 
			const shared_ptr<vector<string>>& texts)
		: element_(key),
		  lines_(lines),
		  texts_(texts)
	{

	}

	void printResult()
	{
		cout << "find the key word:" << element_ << endl;
		for (auto n = lines_->begin(); n != lines_->end(); ++ n)
		{
			cout << "[" << *n << "]" << texts_->at(*n) << endl;
		}
	}
	
	shared_ptr<set<TextQuery::line_n>>& lines()
	{
		return lines_;
	}

	shared_ptr<vector<string>>& texts()
	{
		return texts_;
	}

	size_t maxLine()
	{
		return texts_->size();
	}
private:
	string element_;
	shared_ptr<set<TextQuery::line_n>> lines_;
	shared_ptr<vector<string>> texts_;
};


QueryResult TextQuery::runSearch(const string& str) const
{
	static shared_ptr<set<line_n>> nodata = make_shared<set<line_n>>();
	auto iter = text_map_.find(str);
	if (iter != text_map_.end())
		return QueryResult(str, iter->second, text_);
	else
		return QueryResult(str, nodata, text_);

}

///////////////////////////////////////////////////////////////////////////////////////////

#endif /* TEXT_QUERY_NEW_H_H */

