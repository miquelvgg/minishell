/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 10:12:20 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hd_set_delim(t_action *act)
{
	size_t	len;
	char	q;
	char	*new;

	act->heredoc_expand = 1;
	if (!act->infile)
		return ;
	len = ft_strlen(act->infile);
	q = act->infile[0];
	if ((q == '\'' || q == '\"') && len >= 2 && act->infile[len - 1] == q)
	{
		act->heredoc_expand = 0;
		new = ft_substr(act->infile, 1, len - 2);
		free(act->infile);
		act->infile = new;
	}
}

static int	hd_prepare_one(t_data *data, t_action *act)
{
	pid_t	pid;
	int		status;
	int		fd_r;
	int		fd_w;

	hd_set_delim(act);
	if (hd_open_tmpfile_2fds(&fd_r, &fd_w) < 0)
		return (-1);
	pid = hd_fork_reader(fd_w, data, act);
	if (pid < 0)
		return (close(fd_r), close(fd_w), -1);
	close(fd_w);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (close(fd_r), -2);
	act->heredoc_fd = fd_r;
	return (0);
}

int	ft_prepare_heredocs(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->n_actions)
	{
		if (data->actions[i].heredoc == 1)
		{
			ret = hd_prepare_one(data, &data->actions[i]);
			if (ret < 0)
				return (ret);
		}
		i++;
	}
	return (0);
}

void	ft_close_heredocs(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_actions)
	{
		if (data->actions[i].heredoc_fd >= 0)
		{
			close(data->actions[i].heredoc_fd);
			data->actions[i].heredoc_fd = -1;
		}
		i++;
	}
}
