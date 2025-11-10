#include "minishell.h"
/*
PWD built-in implementation
Takes argv Command and arguments
Takes shell Minishell structure
*/
void	execute_pwd(char **argv, t_minishell *shell)
{
	char	cwd[PATH_MAX];

	(void)argv;
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_printf("%s\n", cwd);
		shell->last_exit_status = 0;
	}
	else
	{
		perror("minishell: pwd");
		shell->last_exit_status = 1;
	}
}
