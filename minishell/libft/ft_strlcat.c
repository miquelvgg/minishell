/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:13:07 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 12:13:15 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_dst = 0;
	while (dst[len_dst] && len_dst < size)
		len_dst++;
	len_src = 0;
	while (src[len_src])
		len_src++;
	if (len_dst == size)
		return (size + len_src);
	i = 0;
	while (src[i] && (len_dst + i + 1) < size)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	if ((len_dst + i) < size)
		dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
