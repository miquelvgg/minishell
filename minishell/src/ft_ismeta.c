#include "minishell.h"

int	ft_ismeta(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '|' || \
	c == '&' || c == ';' || c == '(' || c == ')' || c == '<' || c == '>')
	{
		return (1);
	}
	return (0);
}
