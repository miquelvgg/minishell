#include "minishell.h"

int	is_token(char *s)
{
	if (is_word(s) || is_controlop(s) || is_redop(s))
		return (1);
	return (0);
}
