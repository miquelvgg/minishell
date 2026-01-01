/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2026/01/01 18:14:39 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// control pipe 
int	ms_check_pipe_syntax(t_data *dt)
{
	int	i;

	i = 0;
	if (!dt->token || !dt->token[0])
		return (0);
	if (dt->token[0]->type == T_PIPE)
		return (ms_syntax_err_pipe(dt));
	if ((dt->token[0]->type == T_APPEND) && ((dt->token[1]) && \
	(dt->token[1]->type > T_CMD)))
		return (prt_error("syntax error near unexpected token"), 1);
	while (dt->token[i])
	{
		if (dt->token[i]->type == T_PIPE)
			if (!dt->token[i + 1] || dt->token[i + 1]->type == T_PIPE)
				return (ms_syntax_err_pipe(dt));
		if (dt->token[i]->type == T_RDIR_IN)
			if (!dt->token[i + 1] || dt->token[i + 1]->type == T_RDIR_IN)
				return (prt_error("syntax error near unexpected token"), 1);
		if (dt->token[i]->type == T_RDIR_OUT)
			if (!dt->token[i + 1] || dt->token[i + 1]->type == T_RDIR_OUT)
				return (prt_error("syntax error near unexpected token"), 1);
		i++;
	}
	return (0);
}

static int	cleanup_and_ret(t_data *data, char ***atoken, int ntoken, int code)
{
	free_token(atoken, ntoken);
	free_actions(data);
	free_data_struc(data);
	return (code);
}

static int	process_tokens(t_data *data, char ***atoken, int ntoken)
{
	int	rt;
	int	ret;

	rt = ft_syntax(data, atoken, ntoken);
	if (!rt)
		rt = ms_check_pipe_syntax(data);
	if (!rt)
	{
		rt = ft_actions(data);
		if (!rt)
		{
			ret = ft_prepare_heredocs(data);
			if (ret < 0)
			{
				if (ret == -2)
					data->xstatus = 130;
				return (cleanup_and_ret(data, atoken, ntoken, 1));
			}
			exactions(data);
			ft_close_heredocs(data);
		}
	}
	return (cleanup_and_ret(data, atoken, ntoken, 0));
}

static int	exec_line(t_data *data, char *line)
{
	char	**atoken;
	int		ntoken;

	atoken = NULL;
	if (g_signal == (int)SIGQUIT || !line)
	{
		write(1, "exit\n", 5);
		free(line);
		return (-1);
	}
	if (*line)
	{
		add_history(line);
		ntoken = shell_tokenize(line, &atoken);
		if (ntoken > 0)
		{
			if (process_tokens(data, &atoken, ntoken))
			{
				free(line);
				return (1);
			}
		}
	}
	free(line);
	return (0);
}

int	mshell(t_data *data)
{
	char	*line;
	int		status;

	using_history();
	setup_signals();
	while (1)
	{
		g_signal = 0;
		line = readline(READLINE_MSG);
		status = exec_line(data, line);
		if (status == -1)
			break ;
		if (status == 1)
			return (clear_history(), 1);
	}
	return (clear_history(), 0);
}
