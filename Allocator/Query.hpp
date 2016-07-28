#include "TextQuery_new.hpp"
#include <algorithm>

class QueryBase
{
	friend class Query;
protected:
	using line_n = TextQuery::line_n;
	virtual ~QueryBase() = default;

private:
	virtual string req() const = 0;
	virtual	QueryResult eval(const TextQuery& cursor) const = 0;
};

class Query
{
//	friend ostream& operator<<(ostream& out, const Query& query);
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
public:
	Query(const string&);
	QueryResult eval(const TextQuery& tq) const
	{
		return cursor_->eval(tq);
	}

	string req() const
	{
		return cursor_->req();
	}

private:
	Query(shared_ptr<QueryBase> cursor)
		: cursor_(cursor)
	{

	}

private:
	shared_ptr<QueryBase> cursor_;
};


ostream& operator<<(ostream&  out, const Query& query)
{
	return out << query.req();
}

class WordQuery : public QueryBase
{
	friend class Query;
protected:
	WordQuery(const string& element)
		: element_(element)
	{

	}
private:
	virtual string req() const
	{
//		QueryResult result = eval
		return element_;
	}

	virtual QueryResult eval(const TextQuery& cursor) const
	{
		return cursor.runSearch(element_);
	}

private:
	string element_;
};


Query::Query(const string& str)
	: cursor_(new WordQuery(str))
{
	
}

class NotQuery : public QueryBase
{
	friend Query operator~(const Query& query);
//protected:
	NotQuery(const Query& query)
		: query_(query)
	{

	}
//private:
	virtual string req() const
	{
		return "~(" + query_.req() + ")";
	}

	virtual QueryResult eval(const TextQuery& cursor) const;

//private:
	Query query_;
};

Query operator~(const Query& query)
{
	return shared_ptr<QueryBase>(new NotQuery(query));
}

QueryResult NotQuery::eval(const TextQuery& cursor) const
{
	auto data = query_.eval(cursor);

	size_t max_n = data.maxLine();
	shared_ptr<set<TextQuery::line_n>> temp(new set<TextQuery::line_n>);
	for (size_t i = 0; i < max_n; ++ i)
	{
		if (data.lines()->count(i) == 0)
		{
			temp->insert(i);
		}
	}

	return QueryResult(req(), temp, data.texts());	
}



class BinaryQuery : public QueryBase
{

protected:
	BinaryQuery(const Query& lhs, const Query& rhs, const string& op)
		: lhs_(lhs),
		  rhs_(rhs),
		  op_(op)
	{

	}
//private:
	string req() const
	{
		return lhs_.req() + op_ + rhs_.req();
	}

//	virtual QueryResult eval(TextQuery& cursor) const;
//private:
	Query lhs_, rhs_;
	string op_;
};

class OrQuery : public BinaryQuery
{
	friend Query operator|(const Query& lhs, const Query& rhs);
private:
	OrQuery(const Query& lhs, const Query& rhs)
		: BinaryQuery(lhs, rhs, " | ")
	{

	}

	virtual QueryResult eval(const TextQuery& tq) const;
};

QueryResult OrQuery::eval(const TextQuery& tq) const
{
	auto lhd = lhs_.eval(tq);
	auto lhs = lhd.lines();

	auto rhd = rhs_.eval(tq);
	
	shared_ptr<set<TextQuery::line_n>> temp_lines = 
		make_shared<set<TextQuery::line_n>>(lhs->begin(), lhs->end());
	temp_lines->insert(rhd.lines()->begin(), rhd.lines()->end());

	return QueryResult(req(), lhs, lhd.texts());
}

Query operator|(const Query& lhs, const Query& rhs)
{
	return shared_ptr<QueryBase>(new OrQuery(lhs, rhs));
}

class AndQuery : public BinaryQuery
{
	friend Query operator&(const Query& lhs, const Query& rhs);

	AndQuery(const Query& lhs, const Query& rhs)
		: BinaryQuery(lhs, rhs, " & ")
	{

	}

	virtual QueryResult eval(const TextQuery& tq) const;
};

QueryResult AndQuery::eval(const TextQuery& tq) const
{
	auto lhd = lhs_.eval(tq);
	auto rhd = rhs_.eval(tq);

	shared_ptr<set<TextQuery::line_n>> temp  = make_shared<set<TextQuery::line_n>>();
	
/*	set_union(lhd.lines()->begin(), lhd.lines()->end(), 
			rhd.lines()->begin(), rhd.lines()->end(),
			temp->begin());*/
	for_each(lhd.lines()->begin(), lhd.lines()->end(), [&] (const int x) { if (rhd.lines()->find(x) != rhd.lines()->end())
			temp->insert(x);});

	return QueryResult(req(), temp, lhd.texts());
}

Query operator&(const Query& lhs, const Query& rhs)
{
	return shared_ptr<QueryBase>(new AndQuery(lhs, rhs));
}
