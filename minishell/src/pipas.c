/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:34:15 by epascual          #+#    #+#             */
/*   Updated: 2025/12/29 17:34:16 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Reserva memoria para pipes
int	**mempipas(int max)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = (int **)ft_calloc(sizeof(int *), max);
	if (!pipes)
		return (NULL);
	while (i < max)
	{
		pipes[i] = (int *)ft_calloc(2, sizeof(int));
		if (!pipes[i])
			return (NULL);
		i++;
	}
	return (pipes);
}

//Cierra los pipes
void	closepipes(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->n_actions - 1)
	{
		close(data->pipes[j][0]);
		close(data->pipes[j][1]);
		j++;
	}
}

//Convierte sus pipes en STD y cierra las demas
void	preparepipes(t_action act, t_data *data)
{
	int	i;

	i = act.index;
	if (i > 0)
		dup2(data->pipes[i - 1][0], STDIN_FILENO);
	if (i < data->n_actions -1)
		dup2(data->pipes[i][1], STDOUT_FILENO);
	closepipes(data);
}

//Libera los pipes en caso de error
int	liberapipes(int **pipes, int i)
{
	while (i > 0)
	{
		close(pipes[i - 1][0]);
		close(pipes[i - 1][1]);
		free(pipes[i - 1]);
		i--;
	}
	free(pipes);
	return (0);
}

//Inicia los pipes
int	initpipes(int **pipes, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pipe(pipes[i]) < 0)
			return (liberapipes(pipes, i));
		i++;
	}
	return (1);
}
