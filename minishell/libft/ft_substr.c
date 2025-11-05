/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:14:35 by mvives-s          #+#    #+#             */
/*   Updated: 2024/10/10 17:54:56 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_getvoid(void)
{
	char	*p_res;

	p_res = malloc(1 * sizeof(char));
	if (!p_res)
		return (NULL);
	p_res[0] = '\0';
	return (p_res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	str_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	str_len = 0;
	while (s[str_len] != '\0')
		str_len++;
	if (start >= str_len)
		return (ft_getvoid());
	if (str_len - start < len)
		len = str_len - start;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
