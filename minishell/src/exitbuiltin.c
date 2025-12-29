/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitbuiltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:35:23 by epascual          #+#    #+#             */
/*   Updated: 2025/12/29 13:35:24 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Imprime el  numeric argument error
static void	exiterror(char *ar, t_data *shell)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(ar, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	shell->xstatus = 2;
	exit(shell->xstatus);
}

//Ejecuta exit como lo hace bash
void	execute_exit(char **argv, t_data *shell)
{
	ft_printf("exit\n");
	if (!argv[1])
		exit(0);
	if (!is_valid_number(argv[1]))
		exiterror(argv[1], shell);
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->xstatus = 1;
		return ;
	}
	shell->xstatus = (unsigned char)ft_atoi(argv[1]);
	exit(shell->xstatus);
}
