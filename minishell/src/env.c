#include "minishell.h"

//Ejecuta env ignorando argumentos
void	execute_env(char **argv, t_data *shell)
{
	int	i;
	int max;

	(void)argv;
	i = 0;
	max = ft_stringlen(shell->env);
	while (shell->env[i] && max)
	{
		ft_printf("%s\n", shell->env[i]);
		i++;
	}
	errno = 0;
}
