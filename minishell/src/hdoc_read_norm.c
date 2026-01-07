/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_reader_norm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 10:12:20 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hd_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static int	hd_is_delim(const char *line, const char *delim)
{
	size_t	len;

	if (!line || !delim)
		return (0);
	len = ft_strlen(delim);
	if (ft_strlen(line) != len)
		return (0);
	return (ft_strncmp(line, delim, len) == 0);
}

static void	hd_write_line(int fd, t_data *data, t_action *act, char *line)
{
	char	*out;

	out = line;
	if (act->heredoc_expand == 1)
		out = hd_expand_line(data, line);
	if (!out)
		out = line;
	write(fd, out, ft_strlen(out));
	write(fd, "\n", 1);
	if (out != line)
		free(out);
}

static void	hd_child_loop(int fd, t_data *data, t_action *act)
{
	char	*line;

	signal(SIGINT, hd_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_signal = 0;
		line = readline("> ");
		if (g_signal == (int)SIGQUIT || !line)
		{
			free(line);
			break ;
		}
		if (hd_is_delim(line, act->infile))
		{
			free(line);
			break ;
		}
		hd_write_line(fd, data, act, line);
		free(line);
	}
	close(fd);
	_exit(0);
}

pid_t	hd_fork_reader(int fd, t_data *data, t_action *act)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		hd_child_loop(fd, data, act);
	return (pid);
}
