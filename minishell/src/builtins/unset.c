#include "minishell.h"
/*
Unset built-in implementation
Takes argv Command and arguments
Takes shell Minishell structure
*/
void	execute_unset(char **argv, t_minishell *shell)
{
	int	i;

	if (!argv[1])
	{
		shell->last_exit_status = 0;
		return ;
	}
	i = 1;
	while (argv[i])
	{
		unset_env_var(shell, argv[i]);
		i++;
	}
	shell->last_exit_status = 0;
}
