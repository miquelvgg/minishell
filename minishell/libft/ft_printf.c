/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:52:53 by mvives-s          #+#    #+#             */
/*   Updated: 2024/10/16 11:58:30 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_process_format(const char *format, int *i, va_list args)
{
	int	count;

	count = 0;
	if (format[*i] == 'c')
		count += ft_print_char(va_arg(args, int));
	else if (format[*i] == 's')
		count += ft_print_string(va_arg(args, char *));
	else if (format[*i] == 'p')
		count += ft_print_pointer(va_arg(args, void *));
	else if (format[*i] == 'd' || format[*i] == 'i')
		count += ft_print_decimal(va_arg(args, int));
	else if (format[*i] == 'u')
		count += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format[*i] == 'x' || format[*i] == 'X')
		count += ft_print_hex(va_arg(args, unsigned int), format[*i]);
	else if (format[*i] == '%')
		count += ft_print_percent();
	else
		count += ft_print_char(format[*i]);
	return (count);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_process_format(format, &i, args);
		}
		else
		{
			write(1, &format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
/*
int main (void)
{

	ft_printf("pruebas de numeros %d",939);


}
*/
