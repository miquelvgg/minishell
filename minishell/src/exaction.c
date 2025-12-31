/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:35:23 by epascual          #+#    #+#             */
/*   Updated: 2025/12/29 13:35:24 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Espera a todos los hijos
void	espera(t_data *data, int *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->n_actions)
	{
		waitpid(pids[i], &status, 0);
		if (i == data->n_actions - 1)
		{
			if (WIFEXITED(status))
				data->xstatus = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->xstatus = 128 + WTERMSIG(status);
		}
		i++;
	}
}

static void	close_heredocs_parent(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_actions)
	{
		if (data->actions[i].heredoc_fd != -1)
		{
			close(data->actions[i].heredoc_fd);
			data->actions[i].heredoc_fd = -1;
		}
		i++;
	}
}

static int	exec_builtin_parent(t_action *act, t_data *data)
{
	int	save_in;
	int	save_out;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (save_in < 0 || save_out < 0)
		return (1);
	if (redir_in_parent(act) || redir_out_parent(act))
	{
		perror("minishell");
		data->xstatus = 1;
		dup2(save_in, STDIN_FILENO);
		dup2(save_out, STDOUT_FILENO);
		close(save_in);
		close(save_out);
		return (1);
	}
	execute_builtin(act->argv, data);
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
	return (0);
}

static int checkxcute(t_data*data)
{
	return (data->n_actions == 1 && data->actions[0].argv && \
data->actions[0].argv[0] && is_builtin((data->actions[0]).argv[0]));
}

//Itera las acciones para ejecutarlas
void	exactions(t_data *data)
{
	int	i;
	int	*pid;

	i = 0;
	if (checkxcute(data))
	{
		exec_builtin_parent(&data->actions[0], data);
		return ;
	}
	data->pipes = mempipas(data->n_actions);
	if (initpipes(data->pipes, data->n_actions) == 0)
		exit(1);
	pid = (int *)ft_calloc(sizeof(int), (data->n_actions + 1));
	while (i <= data->n_actions - 1)
	{
		pid[i] = fork();
		if (!pid[i])
			exactionp(data->actions[i], data);
		i++;
	}
	close_heredocs_parent(data);
	closepipes(data);
	espera(data, pid);
	free(pid);
	liberapipes(data->pipes, data->n_actions);
}
