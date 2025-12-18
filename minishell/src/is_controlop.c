#include "minishell.h"

int	is_controlop(char *s)
{
	if (ft_strcmp(s, "||") == 0 || ft_strcmp(s, "&&") == 0
		|| ft_strcmp(s, "&") == 0 || ft_strcmp(s, ";") == 0
		|| ft_strcmp(s, ";;") == 0 || ft_strcmp(s, "(") == 0
		|| ft_strcmp(s, ")") == 0 || ft_strcmp(s, "|") == 0
		|| ft_strcmp(s, "!") == 0)
		return (1);
	return (0);
}
