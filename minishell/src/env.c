#include "minishell.h"

//Ejecuta env ignorando argumentos
void	execute_env(char **argv, t_mshell *shell)
{
	int	i;

	(void)argv;
	i = 0;
	while (shell->env[i])
	{
		ft_printf("%s\n", shell->env[i]);
		i++;
	}
	errno = 0;
}
