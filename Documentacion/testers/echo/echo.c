#include "minishell.h"

static char	echochecknflag(char *str)
{
	while (str){
	if (*str == ' ')
		str++;
	return (1);
	}
	return (0);
}

int echo(char *str)
{
	char	flag;

	flag = echochecknflag(str);
	if (flag)
		fin = "\0"
	else
		fin = "\n"
	printf("%s%s", str, fin);
}
