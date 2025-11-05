#include "minishell.h"

int	is_word(char *s)
{
	while (*s)
	{
		if (*s != ' ' || *s != '\t' || !ft_ismeta(*s))
			return (0);
		s++;
	}
	return (1);
}
