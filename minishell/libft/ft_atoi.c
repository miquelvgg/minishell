/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:14:43 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/25 17:14:46 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fy_isspace(const char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\v'
		|| s[i] == '\f' || s[i] == '\r')
		i++;
	return (i);
}

static int	chk_overf(long result, int sign)
{
	if (sign == 1 && result > 2147483647)
		return (2147483647);
	if (sign == -1 && result > 2147483648)
		return (-2147483648);
	return ((int)(result * sign));
}

int	ft_atoi(const char *str)
{
	long	res;
	int		sig;
	int		i;

	res = 0;
	sig = 1;
	i = fy_isspace(str);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sig = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if ((sig == 1 && res > 2147483647) || (sig == -1 && res > 2147483648))
		{
			return (chk_overf(res, sig));
		}
		i++;
	}
	return (chk_overf(res, sig));
}
