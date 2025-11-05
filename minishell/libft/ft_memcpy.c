/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:11:44 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 12:11:50 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char	*ptr_o;
	unsigned char	*ptr_t;

	if (dest == src || dest == NULL || src == NULL)
		return (dest);
	ptr_o = (unsigned char *) src;
	ptr_t = (unsigned char *) dest;
	while (len-- > 0)
		*(ptr_t++) = *(ptr_o++);
	return (dest);
}
