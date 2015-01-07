#include<iostream>
using namespace std;

bool match(const char* text, const char* name)
{
	if (*text == 0)
	{
		if (*name == '*')
			return true;
		return false;
	}

	if (*name == 0)
	{
		return false;
	}

	if (*name != '*' && *name != '?')
	{
		if (*name == *text)
		{
			return match(text+1, name+1);
		}

		return false;
	}

	if (*name == '?')
	{
		if (!isalpha(*text))
		{
			return false;
		}
        return match(text+1, name+1);

	}

	return match(text, name+1);
}

void scan(const char* pszText, const char* pszName)
{
	if (*pszText == 0)
		return;
	if (*pszName == 0)
		return;

	while(*pszText != 0)
	{
		if (match(pszText, pszName))

	}
}
