#ifndef STRING_PIECE_H_H
#define STRING_PIECE_H_H

#include <string>

class StringArg
{
public:
	StringArg(const char *str)
		: str_(str)
	{

	}
	
	StringArg(const std::string& str)
		: str_(str.c_str())
	{

	}

	const char* c_str()
	{
		return str_;
	}

private:
	const char *str_;
};






#endif /* STRING_PIECE_H_H */
