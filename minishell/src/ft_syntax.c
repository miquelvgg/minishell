/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 10:12:20 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	get_com_built(char *s)
{
	if (!ft_strcmp(s, "echo"))
		return (1);
	else if (!ft_strcmp(s, "cd"))
		return (1);
	else if (!ft_strcmp(s, "pwd"))
		return (1);
	else if (!ft_strcmp(s, "export"))
		return (1);
	else if (!ft_strcmp(s, "unset"))
		return (1);
	else if (!ft_strcmp(s, "evn"))
		return (1);
	else if (!ft_strcmp(s, "exit"))
		return (1);
	return (0);
}

int	get_type(char *str,	int *i)
{
	if (str[*i] == '|')
		return (T_PIPE);
	else if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			*i = *i + 1;
			return (T_APPEND);
		}
		return (T_RDIR_OUT);
	}
	else if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			*i = *i + 1;
			return (T_HERDOC);
		}
		return (T_RDIR_IN);
	}
	if (get_com_built(str))
		return (T_CMD);
	return (T_GENERAL);
}

void	ft_analysis(t_data *dt, char *token, t_token *mtk, int ix)
{
	int		tp;
	int		i;
	char	*tmp;

	i = 0;
	while (token[i])
	{
		tp = get_type(token, &i);
		i++;
	}
	mtk->index = ix;
	mtk->data = token;
	mtk->type = tp;
	tmp = eval_expan(dt, mtk->data);
	mtk->data = tmp;
}

/* tokens --> dt->token  */
/* Guardo los apuntadores del array in icial de todo*/
int	ft_syntax(t_data *dt, char ***tokens, int ntoken)
{
	int		i;
	char	**mtoken;

	i = 0;
	if (!tokens)
		return (-1);
	mtoken = *tokens;
	dt->token = (t_token **) malloc(sizeof(t_token **) * (ntoken + 1));
	if (!dt->token)
		return (-1);
	while ((mtoken[i] != NULL ))
	{
		dt->token[i] = malloc(sizeof(t_token));
		if (!dt->token[i])
		{
			while (--i)
				free(dt->token[i]);
			free(dt->token);
			return (-1);
		}
		ft_analysis(dt, mtoken[i], dt->token[i], i);
		i++;
	}
	dt->token[i] = NULL;
	return (0);
}
