/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex25hate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:53:31 by epascual          #+#    #+#             */
/*   Updated: 2025/04/29 15:54:13 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Las patatas 25 lineas
void	doblefree(char **a, char **b)
{
	ft_free_pointstring(a);
	ft_free_pointstring(b);
}

int	notempty(char **a, char **b)
{
	if (!a || !b || !b)
	{
		doblefree(b, a);
		return (1);
	}
	return (0);
}

int	checkacces(char **s_cmd, char **allpath, char **exec)
{
	(void)allpath;
	(void)exec;	
	(void)s_cmd;
	if (access(*exec, X_OK) == 0)
	{
		doblefree(s_cmd, allpath);
		return (1);
	}
	return (0);
}

//Sale del programa para evitar too many lines
void	finish(int error)
{
	if (error == -2)
	{
		perror(strerror(errno));
		exit(errno);
	}
	else
	{
		perror(strerror(error));
		exit(error);
	}
}

//Cierra fd, para evitar too many lines
void	cierra(int in, int out)
{
	close(in);
	close(out);
}
