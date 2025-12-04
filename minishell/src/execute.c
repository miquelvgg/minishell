#include "minishell.h"

//executa un comando builtin
void	executebuiltin(t_data *minishell, char *str)
{
	char	**s_cmd;

	s_cmd = ft_split(str, ' ');
	printf("Builtin\n");
	execute_builtin(s_cmd, minishell);
	ft_free_pointstring(s_cmd);
}

//executa un comando externo
void	executecomand(t_data *minishell, char *str)
{
	char	*path;
	int		excode;
	char	**s_cmd;
	int		pid;

	excode = 0;
	s_cmd = ft_split(str, ' ');
	printf("No builtin\n");
	pid = fork();
	if (pid == 0)
	{
		printf("%s\n", str);
		path = get_path(str, minishell->env);
		printf("Intenta ejecutar execve\n");
		excode = execve(path, s_cmd, NULL);
		if (excode == -1)
		{
			printf("Fallo execve\n");
			ft_free_pointstring(s_cmd);
			free(path);
			errno = 1;
			exit(errno);
		}
	}
	else
	{
		printf("Padre espera\n");
		waitpid(pid, NULL, 0);
		ft_free_pointstring(s_cmd);
	}
}

//executa un comandoVersion antigua, diferencia aqui entre builtin i comando en lugar de en la tokenizacion
void	execute(t_action act, t_data*minishell)
{
    //printf("%s\n", minishell->token->data);
	char	*path;
	int		excode;
	char	**s_cmd;
	char	*str;
	int		pid;

	excode = 0;
	s_cmd = act.argv;//ft_split(str, ' ');
	str		= s_cmd[0];
	if (is_builtin(s_cmd[0]))
	{
		printf("Builtin\n");
		execute_builtin(s_cmd, minishell);
		ft_free_pointstring(s_cmd);
	}
	else{
		printf("No builtin\n");
		pid = fork();
		if (pid == 0)
		{
			printf("%s\n", str);
            path = get_path(str, minishell->env);
			printf("Intenta ejecutar execve\n");
			excode = execve(path, s_cmd, NULL);
			if (excode == -1)
			{
				printf("Fallo execve\n");
				ft_free_pointstring(s_cmd);
				errno = 1;
				exit(errno);
			}
		}
		else
		{
			printf("Padre espera\n");
			waitpid(pid, NULL, 0);
			ft_free_pointstring(s_cmd);
		}
	}
}
