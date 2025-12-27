#include "minishell.h"

//Ejecuta el builtin pwd
void	execute_pwd(t_data *shell)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_printf("%s\n", cwd);
		shell->xstatus = 0;
	}
	else
	{
		perror("minishell: pwd");
		shell->xstatus = 1;
	}
}
