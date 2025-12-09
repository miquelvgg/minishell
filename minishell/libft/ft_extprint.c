/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:55:38 by mvives-s          #+#    #+#             */
/*   Updated: 2025/12/09 15:04:57 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned int n, char spec)
{
	char	*hex_str;
	int		len;

	hex_str = ft_itoa_base(n, 16);
	if (!hex_str)
		return (0);
	if (spec == 'X')
		ft_strtoupper(hex_str);
	len = ft_print_string(hex_str);
	free(hex_str);
	return (len);
}

int	ft_print_unsigned(unsigned int n)
{
	char	*num_str;
	int		len;

	num_str = ft_utoa(n);
	if (!num_str)
		return (1);
	len = ft_print_string(num_str);
	free(num_str);
	return (len);
}

int	ft_print_decimal(int n)
{
	char	*num_str;
	int		len;

	num_str = ft_itoa(n);
	if (!num_str)
		return (1);
	len = ft_print_string(num_str);
	free(num_str);
	return (len);
}

int	ft_print_pointer(void *ptr)
{
	unsigned long	address;
	char			*hex_str;
	int				len;

	address = (unsigned long)ptr;
	if (ptr == NULL)
		return (write(STDOUT_FILENO, "(nil)", 5));
	write(1, "0x", 2);
	len = 2;
	hex_str = ft_itoa_base(address, 16);
	if (!hex_str)
		return (len);
	len += ft_print_string(hex_str);
	free(hex_str);
	return (len);
}

int	ft_print_string(char *str)
{
	int	len;

	if (!str || !*str)
		str = "(null)";
	len = ft_strlen(str);
	write(1, str, len);
	return (len);
}
