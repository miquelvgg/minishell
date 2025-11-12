#include "minishell.h"

//Ejecuta el builtin pwd
void	execute_pwd()
{
	char	cwd[PATH_MAX];

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
