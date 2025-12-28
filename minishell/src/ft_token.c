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

void	free_token(char ***token, int nt)
{
	int		i;
	char	**mtoken;

	i = 0;
	if ((!token) || (*token == NULL))
		return ;
	mtoken = *token;
	while ((mtoken[i] != NULL ) && (i < nt))
	{
		free(mtoken[i]);
		mtoken[i] = NULL;
		i++;
	}
	free(mtoken);
	mtoken = NULL;
}

/*
** Salta espacios y gestiona el avance del puntero p. (count = inutil)
*/
static const char	*skip_and_move(const char *p, int count)
{
	(void)count;
	while (*p && ((*p >= 9 && *p <= 13) || *p == 32))
		p++;
	return (p);
}

/*
** Determina si un carácter es un metacaracter fuera de comillas.
*/
static int	is_meta(char c, char in_q)
{
	if (in_q)
		return (0);
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

/*
** Escanea una palabra respetando comillas. Los metacaracteres solo 
** detienen el escaneo si in_q (in_quote) es 0.
*/
static const char	*scan_word(const char *p, size_t *raw, int *err)
{
	char	in_q;
	size_t	i;

	in_q = 0;
	i = 0;
	while (p[i])
	{
		if ((p[i] == '\'' || p[i] == '\"') && !in_q)
			in_q = p[i];
		else if (p[i] == in_q)
			in_q = 0;
		else if (!in_q && (((p[i] >= 9 && p[i] <= 13) || p[i] == 32)
				|| is_meta(p[i], in_q)))
			break ;
		i++;
	}
	*raw = i;
	if (in_q)
		*err = 1;
	else
		*err = 0;
	return (p + i);
}

/*
** Cuenta tokens y valida errores de sintaxis o comillas.
*/
int	count_tokens_and_validate(const char *line)
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
				return (ft_putendl_fd("Error: Comillas abiertas", 2), -1);
		}
		p = skip_and_move(p, count++);
	}
	return (count);
}

/*
** Tokenizador principal: extrae metacaracteres o palabras expandibles.
*/
int	shell_tokenize(const char *line, char ***tokens)
{
	int			nt;
	int			k;
	size_t		raw;
	int			err;
	const char	*p;

	nt = count_tokens_and_validate(line);
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