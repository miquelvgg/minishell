/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exacti_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:35:23 by epascual          #+#    #+#             */
/*   Updated: 2025/12/31 12:21:07 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Ejecuta ruta directa
void	directexec(t_action act, t_data*minishell)
{
	int	excode;

	excode = 0;
	is_dir(act.argv[0]);
	existcmd(act.argv[0]);
	is_exec(act.argv[0]);
	excode = execve(act.argv[0], act.argv, minishell->env);
	exit(excode);
}

//executa un pipecomand
void	executep(t_action act, t_data*minishell)
{
	char	*path;
	int		excode;

	excode = 0;
	if (is_builtin(act.argv[0]))
	{
		execute_builtin(act.argv, minishell);
		exit(minishell->xstatus);
	}
	else
	{
		if (ft_strchr(act.argv[0], '/'))
			directexec(act, minishell);
		path = get_path(act.argv[0], minishell->env);
		if (!path)
			existcmd(act.argv[0]);
		excode = execve(path, act.argv, minishell->env);
		if (excode == -1)
		{
			printf("Command not found\n");
			free(path);
			exit(127);
		}
	}
}

//Ejecuta pipe(ultimo)
void	exactionp(t_action act, t_data *data)
{
	preparepipes(act, data);
	if (act.heredoc && act.heredoc_fd != -1)
	{
		dup2(act.heredoc_fd, STDIN_FILENO);
		close(act.heredoc_fd);
	}
	else
		initfdi(&act.fd_in, act.infile);
	if (act.append)
		initfdoa(&act.fd_out, act.outfile);
	else
		initfdo(&act.fd_out, act.outfile);
	executep(act, data);
}
