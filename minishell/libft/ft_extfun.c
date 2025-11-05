/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extfun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:56:10 by mvives-s          #+#    #+#             */
/*   Updated: 2024/10/19 11:56:23 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa(unsigned int n)
{
	char			*str;
	unsigned int	tmp;
	int				len;

	tmp = n;
	len = 0;
	while (tmp)
	{
		tmp = (tmp / 10);
		len++;
	}
	if (n == 0)
		len = 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_itoa_base(unsigned long n, int base)
{
	char			*str;
	char			*rep;
	int				len;
	unsigned long	tmp;

	rep = "0123456789abcdef";
	tmp = n;
	len = 0;
	while (tmp)
	{
		tmp = (tmp / base);
		len++;
	}
	if (n == 0)
		len = 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = rep[n % base];
		n /= base;
	}
	return (str);
}

void	ft_strtoupper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_islower(str[i]))
			str[i] -= 32;
		i++;
	}
}

int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_print_percent(void)
{
	write(1, "%", 1);
	return (1);
}
