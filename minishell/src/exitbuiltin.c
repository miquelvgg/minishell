#include "minishell.h"

//Ejecuta exit como lo hace bash
void	execute_exit(char **argv, t_data *shell)
{
	ft_printf("exit\n");
	if (!argv[1])
		exit(0);
	if (!is_valid_number(argv[1]))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", argv[1]);
		shell->xstatus = 2;
		exit(shell->xstatus);
	}
	if (argv[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		shell->xstatus = 1;
		return ;
	}
	shell->xstatus = (unsigned char)ft_atoi(argv[1]);
	exit(shell->xstatus);
}
