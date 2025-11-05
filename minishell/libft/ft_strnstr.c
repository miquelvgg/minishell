/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:55:26 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/25 10:55:31 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		l;
	char		*pt;

	i = 0;
	l = 0;
	pt = NULL;
	while ((big[i] != '\0') && (i < len))
	{
		if (big[i] == little[l])
			l++;
		if (little[l] == '\0')
			return ((char *)&big[i - (l - 1)]);
		i++;
	}
	return (pt);
}*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] != '\0' && little[j] != '\0'
			&& (i + j) < len && big[i + j] == little[j])
		{
			j++;
		}
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
