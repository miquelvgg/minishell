#include "minishell.h"
/*
Env built-in implementation
Takes argv Command and arguments
Takes shell Minishell structure
*/
void	execute_env(char **argv, t_minishell *shell)
{
	int	i;

	(void)argv;
	i = 0;
	while (shell->envp[i])
	{
		ft_printf("%s\n", shell->envp[i]);
		i++;
	}
	shell->last_exit_status = 0;
}
