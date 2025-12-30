/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  actions_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 10:12:20 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_argv(char **argv)
{
	int	j;

	if (!argv)
		return ;
	j = 0;
	while (argv[j])
	{
		free(argv[j]);
		j++;
	}
	free(argv);
}

static void	free_one_action(t_action *act)
{
	if (act->heredoc_fd != -1)
	{
		close(act->heredoc_fd);
		act->heredoc_fd = -1;
	}
	free_argv(act->argv);
	act->argv = NULL;
	free(act->infile);
	act->infile = NULL;
	free(act->outfile);
	act->outfile = NULL;
}

void	free_actions(t_data *d)
{
	int	i;

	if (!d || !d->actions)
		return ;
	i = 0;
	while (i < d->n_actions)
	{
		free_one_action(&d->actions[i]);
		i++;
	}
	free(d->actions);
	d->actions = NULL;
	d->n_actions = 0;
}

int	count_pipes(t_token **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!tokens)
		return (0);
	while (tokens[i])
	{
		if (tokens[i]->type == T_PIPE)
			count++;
		i++;
	}
	return (count + 1);
}

void	init_action(t_action *act, int index)
{
	act->index = index;
	act->argv = NULL;
	act->infile = NULL;
	act->outfile = NULL;
	act->append = 0;
	act->fd_in = -1;
	act->fd_out = -1;
	act->heredoc = 0;
	act->heredoc_fd = -1;
	act->heredoc_expand = 1;
}
