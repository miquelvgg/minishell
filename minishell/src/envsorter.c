/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envsorter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:13:57 by epascual          #+#    #+#             */
/*   Updated: 2025/12/28 12:40:40 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Intercambia dos posiciones del char**str
static void	ft_swapenv(char **swap, int i, int j)
{
	char	*tmp;

	if (!swap[i] || !swap[j])
		return ;
	tmp = swap[i];
	swap[i] = swap[j];
	swap[j] = tmp;
}

//Hace comprobaciones y ordena el envp
static void	ft_compswap(char***envp, int j)
{
	int		c;
	char	**env;

	env = *envp;
	if (env[j])
	{
		c = 0;
		while (env[j][c] == env[j +1][c])
			c++;
		if (env[j][c] > env[j +1][c])
			ft_swapenv(env, j, j +1);
	}
}

//Recorre para ordenar Alfabeticamente el char**
void	ft_sortpstr(char***envp)
{
	char	**env;
	int		i;
	int		j;
	int		m;

	env = *envp;
	m = ft_stringlen(env) - 1;
	i = 0;
	while (i < m)
	{
		j = 0;
		while (j < m)
		{
			ft_compswap(envp, j);
			j++;
		}
		i++;
	}
}
