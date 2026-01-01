/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:33:38 by epascual          #+#    #+#             */
/*   Updated: 2025/12/29 17:33:39 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Imprime el error de invalid identifier
void	prt_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ms_syntax_err_pipe(t_data *dt)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	dt->xstatus = 2;
	return (1);
}

//Imprime el error de invalid identifier
void	print_findfile_error(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(1);
}
