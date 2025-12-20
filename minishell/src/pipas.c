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
