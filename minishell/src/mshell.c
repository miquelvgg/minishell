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
/*
void	print_actions(t_data *d)
{
	int		i;
	int		j;
	t_action *act;

	if (!d) {
		printf("print_actions: data es NULL\n");
		return;
	}
	if (!d->actions || d->n_actions <= 0) {
		printf("print_actions: no hay acciones\n");
		return;
	}
	
	printf("===== ACCIONES (total: %d) =====\n", d->n_actions);
	i = 0;
	while (i < d->n_actions)
	{
		act = &d->actions[i];
		printf("---- Acción %d ----\n", i);
		printf("index   : %d\n", act->index);

		printf("argv    : ");
		if (!act->argv)
			printf("(null)\n");
		else 
		{
			j = 0;
			while (act->argv[j])
			{
				printf("[%d] \"%s\"  ", j, act->argv[j]);
				j++;
      		}
		if (j == 0)
			printf("(vacío)");
		printf("\n");
	}

	printf("infile  : %s\n", act->infile ? act->infile : "(null)");
	printf("outfile : %s\n", act->outfile ? act->outfile : "(null)");
	printf("append  : %d\n", act->append);


	printf("fd_in   : %d\n", act->fd_in);
	printf("fd_out  : %d\n", act->fd_out);
	printf("heredoc   : %d\n", act->heredoc);
	printf("heredoc_fd: %d\n", act->heredoc_fd);

	printf("--------------------\n");
	i++;
	}
	printf("===== FIN ACCIONES =====\n");
}

//Libera el data struct

//Imprime los tokens
void paint_token(t_data	*data)
{
	int		i;
	t_token **mtoken;
	
	i = 0;
	if (!data->token)
    	return;
	mtoken = data->token;
	
	while ((mtoken[i] != NULL))
	{
		printf("(%d) %s type(%d)\n", i, mtoken[i]->data,mtoken[i]->type);
		i++;
	}
}
		//print_actions(data);
		//paint_token(data);

*/
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
		rt = ft_actions(data);
	if (rt)
		return (cleanup_and_ret(data, atoken, ntoken, 1));
	ret = ft_prepare_heredocs(data);
	if (ret < 0)
	{
		if (ret == -2)
			data->xstatus = 130;
		return (cleanup_and_ret(data, atoken, ntoken, 1));
	}
	exactions(data);
	ft_close_heredocs(data);
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
