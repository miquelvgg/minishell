#include "minishell.h"

//Ejecuta sin pipe(ultimo)
void	exaction(t_action act, t_data*data)
{
	if (act.append)
		initfdoa(&act.fd_out, act.outfile);
	else
		initfdo(&act.fd_out, act.outfile);
	initfdi(&act.fd_in, act.infile);
	execute(act, data);
}

//Ejecuta pipe(ultimo)
void	exactionp(t_action act, t_data*data)
{
	printf("Habria aqui pipe\n");
	if (act.append)
		initfdoa(&act.fd_out, act.outfile);
	else
		initfdo(&act.fd_out, act.outfile);
	initfdi(&act.fd_in, act.infile);
	executep(act, data);
}

//Ejecuta con pipe
/*
//Ejecuta con pipe
void	exactionp(t_action act, t_data*data)
{
	t_pid	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit(-2);
	pid = fork();
	if (pid == -1)
		exit(-2);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		execute(act, data);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		waitpid(pid, NULL, 0);
	}
}
*/
void	exactions(t_data*data)
{
	int	i;

	i = 0;
	while(i < data->n_actions - 1)
	{
		printf("%i de %i\n", i, data->n_actions);
		exactionp(data->actions[i], data);
		i++;
	}
	if (i == data->n_actions -1)
	{
		printf("%i de %i\n", i, data->n_actions);
		exaction(data->actions[i], data);
	}
}
