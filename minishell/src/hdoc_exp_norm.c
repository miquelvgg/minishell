/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_exp_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 10:12:20 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	hd_put_status(t_hdexp *e)
{
	char	*st;

	st = ft_itoa((int)e->dt->xstatus);
	if (!st)
		return (0);
	if (!append_to_buff(&e->out, &e->len, st, (int)ft_strlen(st)))
		return (free(st), 0);
	free(st);
	return (1);
}

static int	hd_put_var(t_hdexp *e)
{
	int		vlen;
	char	*name;
	char	*val;

	vlen = extract_var_name_len(e->s + e->i + 1);
	if (vlen <= 0)
		return (append_to_buff(&e->out, &e->len, "$", 1));
	name = ft_substr(e->s, e->i + 1, vlen);
	if (!name)
		return (0);
	if (name[0] == '?' && name[1] == '\0')
	{
		free(name);
		return (hd_put_status(e));
	}
	val = get_var_value(e->dt, name);
	free(name);
	if (val)
		return (append_to_buff(&e->out, &e->len, val, (int)ft_strlen(val)));
	return (1);
}

static int	hd_step(t_hdexp *e)
{
	if (e->s[e->i] == '$')
	{
		if (!hd_put_var(e))
			return (0);
		e->i += 1 + extract_var_name_len(e->s + e->i + 1);
		return (1);
	}
	if (!append_to_buff(&e->out, &e->len, &e->s[e->i], 1))
		return (0);
	e->i++;
	return (1);
}

char	*hd_expand_line(t_data *data, const char *line)
{
	t_hdexp	e;

	e.dt = data;
	e.s = line;
	e.i = 0;
	e.len = 0;
	e.out = (char *)malloc(1);
	if (!e.out)
		return (NULL);
	e.out[0] = '\0';
	while (e.s[e.i])
	{
		if (!hd_step(&e))
			return (free(e.out), NULL);
	}
	return (e.out);
}
