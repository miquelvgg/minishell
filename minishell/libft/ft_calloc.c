/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:05:51 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/25 18:07:10 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p_ret;
	char	*cl;
	size_t	i;

	if ((nmemb != 0) && (size != 0) && (nmemb > ((size_t)-1) / size))
		return (NULL);
	p_ret = malloc(nmemb * size);
	if (!p_ret)
		return (NULL);
	cl = (char *) p_ret;
	i = 0;
	while (i < (nmemb * size))
	{
		cl[i++] = 0;
	}
	return (p_ret);
}
