#include "minishell.h"

/*
Check if string is a valid number (handles +/- prefix)
Takes str String to check
Return 1 if valid number, 0 otherwise
*/
static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
Validates if a string is a valid variable identifier
Takes str String to validate (can be "VAR" or "VAR=value")
Returns 1 if valid, 0 if invalid
*/
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] == '=' && i == 0)
		return (0);
	return (1);
}
