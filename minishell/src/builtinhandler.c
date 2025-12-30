/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinhandler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:19:16 by epascual          #+#    #+#             */
/*   Updated: 2025/12/30 11:41:45 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Comprueba si un comando es un Builtin
int	is_builtin(char *cmd)
{
	if (!cmd || !cmd[0])
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

//Ejecuta los builtins si los encuentra
void	execute_builtin(char **argv, t_data *shell)
{
	if (!argv || !argv[0] || !argv[0][0])
		return ;
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		execute_pwd(shell);
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
		ft_printf("minishell: %s: builtin no implementado\n", argv[0]);
}
