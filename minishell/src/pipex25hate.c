/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex25hate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:53:31 by epascual          #+#    #+#             */
/*   Updated: 2025/11/29 14:52:30 by epascual         ###   ########.fr       */
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

//Cierra fd, para evitar too many lines
void	cierra(int in, int out)
{
	close(in);
	close(out);
}
