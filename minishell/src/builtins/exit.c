#include "minishell.h"
/*
Exit built-in implementation
Takes argv Command and arguments
Takes shell Minishell structure
*/
void	execute_exit(char **argv, t_minishell *shell)
{
	int		exit_code;
	long	num;

	ft_printf("exit\n");
	if (!argv[1])
	{
		exit(shell->last_exit_status);
	}
	if (!is_valid_number(argv[1]))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", argv[1]);
		exit(2);
	}
	if (argv[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		shell->last_exit_status = 1;
		return ;
	}
	num = ft_atoi(argv[1]);
	exit_code = (unsigned char)num;
	exit(exit_code);
}
