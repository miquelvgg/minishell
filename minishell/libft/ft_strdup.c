/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:42:29 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/25 18:42:32 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		l;
	char	*p_res;

	if (s == NULL)
		return (NULL);
	l = 0;
	while (s[l] != '\0')
		l++;
	p_res = malloc((l + 1) * sizeof(char));
	if (!p_res)
		return (NULL);
	i = 0;
	while (i < l)
	{
		p_res[i] = s[i];
		i++;
	}
	p_res[i] = '\0';
	return (p_res);
}
