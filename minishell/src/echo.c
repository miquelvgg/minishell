/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:15:49 by epascual          #+#    #+#             */
/*   Updated: 2025/12/28 12:15:53 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Comprueba la existencia de una flag en un string
static int	ft_flag(char *str, char c, void *flag)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] == c)
		i++;
	if (i >= 2 && (str[i] == '\0' || ft_isspace(str[i])))
	{
		*(int *)flag = 0;
		return (1);
	}
	return (0);
}

//Ejecuta echo
void	execute_echo(char **argv, t_data *shell)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (argv[i] && ft_flag(argv[i], 'n', &newline) == 1)
		i++;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	shell->xstatus = 0;
}
/*main de prueba, va correctamente
int	main(int c, char **argv)
{
	c = 0;
	execute_echo(argv);
	return (0);
}*/
