#include "minishell.h"

int	is_filename(const char *s)
{
	if (s == NULL || *s == '\0')
		return (1);
	while (*s)
	{
		if (*s == '/' || *s == '\0')
			return (1);
		s++;
	}
	return (0);
}
