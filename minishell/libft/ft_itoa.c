/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:29:22 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/30 16:29:27 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_reverse(char *s, size_t len)
{
	char	tmp;
	size_t	i;
	size_t	f;

	if (len == 0)
		return ;
	i = 0;
	f = len - 1;
	while (i < f)
	{
		tmp = s[i];
		s[i] = s[f];
		s[f] = tmp;
		i++;
		f--;
	}
}

static size_t	get_num_length(int n)
{
	size_t	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*allocate_memory(size_t len)
{
	char	*p_num;

	p_num = (char *)malloc(sizeof(char) * (len + 1));
	if (!p_num)
		return (NULL);
	return (p_num);
}

static size_t	neg_number(int n, long *num, char *p_num)
{
	size_t	i;

	*num = n;
	i = 0;
	if (n < 0)
	{
		*num = -(*num);
		p_num[i++] = '-';
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*p_num;
	long	num;
	size_t	i;
	size_t	len;

	len = get_num_length(n);
	p_num = allocate_memory(len);
	if (!p_num)
		return (NULL);
	i = neg_number(n, &num, p_num);
	if (num == 0)
		p_num[i++] = '0';
	while (num > 0)
	{
		p_num[i++] = '0' + (num % 10);
		num = num / 10;
	}
	if (n < 0)
		ft_reverse(p_num + 1, i - 1);
	else
		ft_reverse(p_num, i);
	p_num[i] = '\0';
	return (p_num);
}
