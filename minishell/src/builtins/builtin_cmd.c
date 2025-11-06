/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdellaza <rdellaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 09:03:18 by rdellaza          #+#    #+#             */
/*   Updated: 2025/11/01 01:45:36 by rdellaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/minishell.h"

/*
Echo built-in implementation
Takes argv Command and arguments
Takes shell Minishell structure
*/
void	execute_echo(char **argv, t_minishell *shell)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	if (argv[1] && ft_strncmp(argv[1], "-n", 3) == 0)
	{
		newline = 0;
		i = 2;
	}
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	shell->last_exit_status = 0;
}

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

/*
CD built-in implementation
Takes argv Command and arguments
Takes shell Minishell structure
*/
void	execute_cd(char **argv, t_minishell *shell)
{
	char	*path;
	char	old_pwd[PATH_MAX];

	if (check_cd_args(argv, shell))
		return ;
	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		perror("minishell: cd: getcwd");
		shell->last_exit_status = 1;
		return ;
	}
	path = get_cd_target_path(argv, shell);
	if (!path)
		return ;
	change_directory(path, shell);
}

/*
Check if string is a valid number (handles +/- prefix)
Takes str String to check
Return 1 if valid number, 0 otherwise
*/
static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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
