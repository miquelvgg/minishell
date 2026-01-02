/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:13:07 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 12:13:15 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	p_error(t_data *data, int opc)
{
	int	err ;

	err = -1;
	if (opc == 1)
	{
		data->xstatus = 200;
		err = -1;
		ft_putendl_fd("Error: Comillas abiertas", 2);
	}
	return (err);
}

/*
** Cuenta tokens y valida errores de sintaxis o comillas.
*/
int	count_tokens_and_validate(t_data *data, const char *line)
{
	int			count;
	size_t		raw;
	int			err;
	const char	*p;

	count = 0;
	p = skip_and_move(line, count);
	while (*p)
	{
		if (is_meta(*p, 0))
		{
			if ((*p == '<' || *p == '>') && *(p + 1) == *p)
				p += 2;
			else
				p += 1;
		}
		else
		{
			p = scan_word(p, &raw, &err);
			if (err)
				return (p_error(data, 1));
		}
		p = skip_and_move(p, count++);
	}
	return (count);
}

/*
** Tokenizador principal: extrae metacaracteres o palabras expandibles.
*/
int	shell_tokenize(t_data *data, const char *line, char ***tokens)
{
	int			nt;
	int			k;
	size_t		raw;
	int			err;
	const char	*p;

	nt = count_tokens_and_validate(data, line);
	if (nt <= 0)
		return (nt);
	*tokens = (char **)malloc(sizeof(char *) * (nt + 1));
	if (!*tokens)
		return (-1);
	p = skip_and_move(line, nt);
	k = 0;
	while (k < nt)
	{
		if (is_meta(*p, 0))
			raw = (1 + ((*p == '<' || *p == '>') && *(p + 1) == *p));
		else
			scan_word(p, &raw, &err);
		(*tokens)[k++] = ft_substr(p, 0, raw);
		p = skip_and_move(p + raw, nt);
	}
	(*tokens)[k] = NULL;
	return (k);
}
