/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:27:58 by epascual          #+#    #+#             */
/*   Updated: 2025/12/28 12:28:04 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Ejecuta unset builtin
void	execute_unset(char **argv, t_data *shell)
{
	int	i;

	if (!argv[1])
	{
		shell->xstatus = 0;
		return ;
	}
	i = 1;
	while (argv[i])
	{
		unset_env_var(shell, argv[i]);
		i++;
	}
	shell->xstatus = 0;
}
