/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:40:02 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/24 18:40:40 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*slast;
	char	ch;

	slast = NULL;
	ch = (char)c;
	while (*s != '\0')
	{
		if (*s == ch)
			slast = (char *)s;
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (slast);
}
