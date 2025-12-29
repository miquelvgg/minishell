/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 10:12:20 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// variable x_status
static int	handle_status(t_data *dt, t_buf *b)
{
	char	*status_str;
	int		ret;

	status_str = ft_itoa((int)dt->xstatus);
	if (!status_str)
		return (0);
	ret = append_to_buff(&b->buff, &b->len, \
		status_str, ft_strlen(status_str));
	free(status_str);
	return (ret);
}

static int	handle_var(t_data *dt, t_buf *b, char *var_name)
{
	char	*val;

	if (var_name[0] == '?' && var_name[1] == '\0')
		return (handle_status(dt, b));
	val = get_var_value(dt, var_name);
	if (val)
	{
		if (!append_to_buff(&b->buff, &b->len, val, ft_strlen(val)))
			return (0);
	}
	return (1);
}

static int	expand_var(t_expan *e)
{
	int		vlen;
	char	*vname;

	(e->i)++;
	vlen = extract_var_name_len(&e->str[e->i]);
	if (vlen > 0)
	{
		vname = strndup_safe(&e->str[e->i], vlen);
		if (!vname)
			return (0);
		if (!handle_var(e->dt, &e->buf, vname))
			return (free(vname), 0);
		free(vname);
		e->i += vlen;
		return (1);
	}
	return (append_to_buff(&e->buf.buff, &e->buf.len, "$", 1));
}

static void	update_q(char c, char *q)
{
	if (*q == 0)
		*q = c;
	else
		*q = 0;
}

char	*eval_expan(t_data *dt, const char *str)
{
	t_expan	e;

	e.buf.buff = malloc(1);
	if (!e.buf.buff)
		return (NULL);
	e.dt = dt;
	e.buf.len = 0;
	e.str = str;
	e.i = 0;
	e.q = 0;
	while (str[e.i])
	{
		if ((str[e.i] == '\'' || str[e.i] == '"') && \
			(e.q == 0 || e.q == str[e.i]))
			update_q(str[e.i++], &e.q);
		else if (str[e.i] == '$' && e.q != '\'')
		{
			if (!expand_var(&e))
				return (free(e.buf.buff), NULL);
		}
		else if (!append_to_buff(&e.buf.buff, &e.buf.len, &str[e.i++], 1))
			return (free(e.buf.buff), NULL);
	}
	return (e.buf.buff);
}
