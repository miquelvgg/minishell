#include "minishell.h"
// 32 Keywords are checked in this function and return the
// result accordingly
bool	isKeyword(char* str)
{

	(void)str;
	/*int i;
	const char* keywords[];
	keywords = { "if", "then", "elif", "else", "fi", "time", "for", "in", "until", "while", "do", "done", "case", "esac", "coproc", "select", "function", "{", "}", "[[", "]]", "!"};
	i = 0;
	while (i < sizeof(keywords) / sizeof(keywords[0]))
	{
		if (strcmp(str, keywords[i]) == 0) 
		{
			return (true);
		}
		i++;
	}*/
	return (false);
}
