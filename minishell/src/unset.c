#include "minishell.h"

//Ejecuta unset builtin
void	execute_unset(char **argv, t_mshell *shell)
{
	int	i;

	if (!argv[1])
	{
		errno = 0;
		return ;
	}
	i = 1;
	while (argv[i])
	{
		unset_env_var(shell, argv[i]);
		i++;
	}
	errno = 0;
}
