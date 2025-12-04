#include "minishell.h"

void	exaction(t_action act, t_data*data)
{
	if (act.append)
		initfdoa(&(act.fd_out), act.outfile);
	else
		initfdo(&(act.fd_out), act.outfile);
	initfdi(&(act.fd_in), act.infile);
	execute(act, data);
}

void	exactions(t_data*data)
{
	int	i;

	i = 0;
	while(i < data->n_actions)
	{
		exaction(data->actions[i], data);
	}
}
