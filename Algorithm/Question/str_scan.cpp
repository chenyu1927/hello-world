#include <iostream>
using namespace std;
//FIXME : * ? 
//

const char* end = NULL;
bool match(const char* text, const char* name)
{
	if (*name == '\0')
	{
		end = text;
		return true;
	}

	if (*text == '\0')
	{
		if (*name == '*')
		{
			end = text;
			return true;
		}
	}

	if (*name != '*' && *name != '?')
	{
		if (*name == *text)
		{
			return match(name+1, text+1);
		}
		return false;
	}
	else
	{
		if (*name == '*')
		{
			return match(text, name+1) || match(text+1, name);
		}
		else
		{
			return match(text+1, name+1);
		}
	}
}

void scan(const char* text, const char* name)
{
	while (*text != '\0')
	{
		if (match(text, name))
		{
			while (text != end)
			{
				cout << *text++;
			}
			cout << endl;
		}
	}

}

int main(void)
{
	char *text = "chysdlkfj, chenyu, chhhhhyyy";
	char *name = "ch*y";

	scan(text, name);
	return 0;
}
