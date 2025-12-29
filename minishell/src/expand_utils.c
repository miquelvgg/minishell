/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:45:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/20 20:45:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_var_name_len(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}

char	*get_var_value(t_data *dt, const char *var_name)
{
	if (!var_name || *var_name == '\0')
		return (NULL);
	if (var_name[0] == '?' && var_name[1] == '\0')
		return (NULL);
	return (search_env(dt, var_name));
}

int	append_to_buff(char **dst, int *curlen, const char *src, int slen)
{
	int		new_len;
	char	*new_dst;

	if (slen <= 0)
		return (1);
	new_len = *curlen + slen;
	new_dst = (char *)ft_realloc(*dst, *curlen, (new_len + 1));
	if (!new_dst)
		return (0);
	*dst = new_dst;
	ft_memcpy(*dst + *curlen, src, slen);
	(*dst)[new_len] = '\0';
	*curlen = new_len;
	return (1);
}
