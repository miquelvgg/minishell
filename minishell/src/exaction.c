#include "minishell.h"

//Cierra los pipes
void	closepipes(t_data*data)
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

//executa un pipecomand
void	executep(t_action act, t_data*minishell)
{
	char	*path;
	int		excode;
	char	**s_cmd;

	excode = 0;
	s_cmd = act.argv;
	path = get_path(s_cmd[0], minishell->env);
	if (!path)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	if (is_builtin(s_cmd[0]))
	{
		printf("Builtin\n");
		execute_builtin(s_cmd, minishell);
		exit(errno);
	}
	else
	{
		excode = execve(path, s_cmd, minishell->env);
		if (excode == -1)
		{
			printf("Fallo execve\n");
			free(path);
			errno = 127;
			exit(errno);
		}
	}
}

void	preparepipes(t_action act, t_data *data)
{
	int	i;

	i = act.index;
	if (i > 0)
		dup2(data->pipes[i - 1][0], STDIN_FILENO);
	if (i < data->n_actions - 1)
		dup2(data->pipes[i][1], STDOUT_FILENO);
	closepipes(data);
}

//Ejecuta pipe(ultimo)
void	exactionp(t_action act, t_data*data)
{
	preparepipes(act, data);
	initfdi(&act.fd_in, act.infile);
	if (act.append)
		initfdoa(&act.fd_out, act.outfile);
	else
		initfdo(&act.fd_out, act.outfile);
	executep(act, data);
}

//Espera a todos los hijos
void	espera(t_data*data, int*pids)
{
	int	i;

	i = 0;
	while (i < data->n_actions)
	{
		waitpid(pids[i], &errno, 0);
		i++;
	}
}

//Itera las acciones para ejecutarlas
void	exactions(t_data*data)
{
	int	i;
	int	*pid;

	i = 0;
	if (data->n_actions == 1 && is_builtin((data->actions[0]).argv[0]))
		execute_builtin((data->actions[0]).argv, data);
	else
	{
		data->pipes = mempipas(data->n_actions);
		if (initpipes(data->pipes, data->n_actions) == 0)
		{
			errno = 1;
			exit(errno);
		}
		pid = (int *)ft_calloc(sizeof(int), (data->n_actions + 1));
		while (i <= data->n_actions - 1)
		{
			pid[i] = fork();
			if (!pid[i])
				exactionp(data->actions[i], data);
			i++;
		}
		closepipes(data);
		espera(data, pid);
		free(pid);
		liberapipes(data->pipes, data->n_actions);
	}
}
