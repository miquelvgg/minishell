#include "minishell.h"
/*
Echo built-in implementation
Takes argv Command and arguments
Takes shell Minishell structure
*/
void	execute_echo(char **argv, t_minishell *shell)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	if (argv[1] && ft_strncmp(argv[1], "-n", 3) == 0)
	{
		newline = 0;
		i = 2;
	}
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	shell->last_exit_status = 0;
}
