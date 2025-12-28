/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:14:07 by epascual          #+#    #+#             */
/*   Updated: 2025/12/28 12:15:14 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Ejecuta env ignorando argumentos
void	execute_env(char **argv, t_data *shell)
{
	int	i;
	int	max;

	(void)argv;
	i = 0;
	max = ft_stringlen(shell->env);
	if (shell->env && shell->env[0])
	{
		while (shell->env[i])
		{
			ft_printf("%s\n", shell->env[i]);
			i++;
		}
	}
	shell->xstatus = 0;
}
