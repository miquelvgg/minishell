/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:13:37 by mvives-s          #+#    #+#             */
/*   Updated: 2024/10/01 17:14:16 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	r;
	char	c;

	r = n;
	if (r < 0)
	{
		write(fd, "-", 1);
		r = r * -1;
	}
	if (r >= 10)
	{
		ft_putnbr_fd(r / 10, fd);
		ft_putnbr_fd(r % 10, fd);
	}
	else
	{
		c = r + '0';
		write(fd, &c, 1);
	}
}
