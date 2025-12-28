/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_actions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 10:12:20 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	add_arg(t_action *act, const char *arg)
{
	int		count;
	char	**new_argv;
	int		i;

	count = 0;
	if (act->argv)
		while (act->argv[count])
			count++;
	new_argv = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return (1);
	i = -1;
	if (act->argv)
		while (++i < count)
			new_argv[i] = act->argv[i];
	new_argv[count] = ft_strdup(arg);
	if (!new_argv[count])
		return ((void)free(new_argv), 1);
	new_argv[count + 1] = NULL;
	if (act->argv)
		free(act->argv);
	act->argv = new_argv;
	return (0);
}

static	int	handle_redir(t_data *dt, int *i, int idx)
{
	t_token		*tok;
	t_token		*next;
	t_action	*act;

	printf("Entras handle_redir\n");
	tok = dt->token[*i];
	next = dt->token[*i + 1];
	act = &dt->actions[idx];
	if (!next)
		return (0);
	if (tok->type == T_RDIR_IN)
		act->infile = ft_strdup(next->data);
	else
	{
		act->outfile = ft_strdup(next->data);
		if (tok->type == T_APPEND)
			act->append = 1;
		else
			act->append = 0;
	}
	if ((tok->type == T_RDIR_IN && (!act->infile)) || \
		(tok->type != T_RDIR_IN && (!act->outfile)))
		return (1);
	(*i)++;
	return (0);
}

static	int	process_token(t_data *dt, int *i, int *act_idx)
{
	int	type;

	type = dt->token[*i]->type;
	if (type == T_PIPE)
	{
		(*act_idx)++;
		if (*act_idx < dt->n_actions)
			init_action(&dt->actions[*act_idx], *act_idx);
	}
	else if (type == T_CMD || type == T_GENERAL)
	{
		if (add_arg(&dt->actions[*act_idx], dt->token[*i]->data))
			return (1);
	}
	else if (type == T_RDIR_IN || type == T_RDIR_OUT || type == T_APPEND)
	{
		if (handle_redir(dt, i, *act_idx))
			return (1);
	}
	return (0);
}

int	ft_actions(t_data *dt)
{
	int	i;
	int	act_idx;

	if (!dt->token)
		return (0);
	dt->n_actions = count_pipes(dt->token);
	dt->actions = malloc(sizeof(t_action) * dt->n_actions);
	if (!dt->actions)
	{
		perror("dt->actions NULL");
		return (1);
	}
	i = 0;
	act_idx = 0;
	init_action(&dt->actions[act_idx], act_idx);
	while (dt->token[i])
	{
		if (process_token(dt, &i, &act_idx))
		{
			perror("process_token Error");
			return (1);
		}
		i++;
	}
	return (0);
}
