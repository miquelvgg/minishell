#include "minishell.h"

//Ejecuta exit como lo hace bash
void	execute_exit(char **argv)
{
	unsigned char	num;

	ft_printf("exit\n");
	if (!argv[1])
		exit(errno);
	if (!is_valid_number(argv[1]))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", argv[1]);
		errno = 2;
		exit(errno);
	}
	if (argv[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		errno = 1;
		return ;
	}
	num = (unsigned char)ft_atoi(argv[1]);
	exit(num);
}
