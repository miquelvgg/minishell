#include "minishell.h"

void	execute(t_data *minishell)
{
	printf("%s\n",minishell->token->data);
	char	*path;
	int		excode;
	char	**s_cmd;
	int		pid;

	excode = 0;
	s_cmd = ft_split(minishell->token->data, ' ');
	if (is_builtin(s_cmd[0]))
			execute_builtin(s_cmd, minishell);
	else
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		path = get_path(s_cmd[0], minishell->env);
		excode = execve(path, s_cmd, NULL);
	}
	if (excode != 0)
	{
		ft_free_pointstring(s_cmd);
	}
}
