/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 10:12:20 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_tokens(t_data *data, char ***atoken, int ntoken)
{
	int	rt;

	rt = ft_syntax(data, atoken, ntoken);
	if (!rt)
		rt = ft_actions(data);
	if (rt)
	{
		free_actions(data);
		free_token(atoken, ntoken);
		free_data_struc(data);
		return (1);
	}
	if ((*atoken) && ntoken && (*atoken)[ntoken - 1][0] == '|')
		printf("Error : pipe\n");
	else
		exactions(data);
	free_token(atoken, ntoken);
	free_actions(data);
	free_data_struc(data);
	return (0);
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

	data->signal_status = 0;
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
			return (1);
	}
	return (0);
}
