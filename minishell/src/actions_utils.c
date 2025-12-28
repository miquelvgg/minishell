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

void	free_actions(t_data *d)
{
	int			i;
	int			j;
	t_action	*act;

	if (!d || !d->actions)
		return ;
	i = -1;
	while (++i < d->n_actions)
	{
		act = &d->actions[i];
		if (act->argv)
		{
			j = -1;
			while (act->argv[++j])
				free(act->argv[j]);
			free(act->argv);
		}
		if (act->infile)
			free(act->infile);
		if (act->outfile)
			free(act->outfile);
	}
	free(d->actions);
	d->actions = NULL;
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
}
