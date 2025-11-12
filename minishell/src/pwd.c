#include "minishell.h"

//Ejecuta el builtin pwd
void	execute_pwd(char **argv, t_mshell *shell)
{
	char	cwd[PATH_MAX];

	(void)argv;
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_printf("%s\n", cwd);
		errno = 0;
	}
	else
	{
		perror("minishell: pwd");
		errno = 1;
	}
}
