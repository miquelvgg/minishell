/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdellaza <rdellaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 09:04:45 by rdellaza          #+#    #+#             */
/*   Updated: 2025/10/31 07:37:11 by rdellaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/minishell.h"

/*
Checks if a command is a built-in
Takes cmd Command name to check
Return 1 if built-in, 0 otherwise
*/
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

/*
Main dispatcher for built-in commands
Takes argv Command and arguments
Takes shell Minishell structure containing environment
*/
void	execute_builtin(char **argv, t_minishell *shell)
{
	if (!argv || !argv[0])
		return ;
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		execute_pwd(argv, shell);
	else if (ft_strncmp(argv[0], "echo", 5) == 0)
		execute_echo(argv, shell);
	else if (ft_strncmp(argv[0], "env", 4) == 0)
		execute_env(argv, shell);
	else if (ft_strncmp(argv[0], "export", 7) == 0)
		execute_export(argv, shell);
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
		execute_unset(argv, shell);
	else if (ft_strncmp(argv[0], "cd", 3) == 0)
		execute_cd(argv, shell);
	else if (ft_strncmp(argv[0], "exit", 5) == 0)
		execute_exit(argv, shell);
	else
		ft_printf("minishell: %s: built-in not yet implemented\n", argv[0]);
}
