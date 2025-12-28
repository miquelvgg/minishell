/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:26:45 by epascual          #+#    #+#             */
/*   Updated: 2025/12/28 12:26:48 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Ejecuta el builtin pwd
void	execute_pwd(t_data *shell)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_printf("%s\n", cwd);
		shell->xstatus = 0;
	}
	else
	{
		perror("minishell: pwd");
		shell->xstatus = 1;
	}
}
