#include "minishell.h"
////		ft_strcmp(s, "&>") == 0	|| ft_strcmp(s, "2>&1") == 0)
int	is_redop(char *s)
{
	if (ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0
		|| ft_strcmp(s, "<") == 0 || ft_strcmp(s, "<<") == 0
		|| ft_strcmp(s, "<>") == 0 )
		return (1);
	return (0);
}
