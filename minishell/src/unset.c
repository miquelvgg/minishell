#include "minishell.h"

//Ejecuta unset builtin
void	execute_unset(char **argv, t_data *shell)
{
	int	i;

	if (!argv[1])
	{
		shell->xstatus = 0;
		return ;
	}
	i = 1;
	while (argv[i])
	{
		unset_env_var(shell, argv[i]);
		i++;
	}
	shell->xstatus = 0;
}
