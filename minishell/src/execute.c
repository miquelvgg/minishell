#include "minishell.h"

//executa un comando builtin
void	executebuiltin(t_data *minishell, char *str)
{
	char	**s_cmd;

	s_cmd = ft_split(str, ' ');
	printf("Builtin\n");//DEBUGEAO
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
	printf("No builtin\n");//DEBUGEAO
	pid = fork();
	if (pid == 0)
	{
		printf("%s\n", str);
		path = get_path(str, minishell->env);
		printf("Intenta ejecutar execve\n");//DEBUGEAO
		excode = execve(path, s_cmd, minishell->env);
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
		printf("Padre espera\n");//DEBUGEAO
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
	if (is_builtin(str))
	{
		printf("Builtin\n");
		execute_builtin(s_cmd, minishell);
		//ft_free_pointstring(s_cmd);
	}
	else{
		printf("No builtin\n");//DEBUGEAO
		pid = fork();
		if (pid == 0)
		{
			printf("%s\n", str);//DEBUGEAO
            path = get_path(str, minishell->env);
			printf("%s\n", path);//DEBUGEAO
			printf("Intenta ejecutar execve\n");//DEBUGEAO
			excode = execve(path, s_cmd, minishell->env);
			if (excode == -1)
			{
				printf("Fallo execve\n");
			//		free_actions(minishell);
			//		free_data_struc(minishell); // free space malloc
		//		ft_free_pointstring(s_cmd);
			//	free(path);
				errno = 127;
				exit(errno);
			}
		}
		else
		{
			printf("Padre espera\n");//DEBUGEAO
			waitpid(pid, NULL, 0);

			if (excode == -1)
				exit(127);
			//ft_free_pointstring(s_cmd);
		}
	}
}


//executa un pipecomand
void	executep(t_action act, t_data*minishell)
{
	char	*path;
	int		excode;
	char	**s_cmd;
	char	*str;
	int		pid;
	int		p_fd[2];

	excode = 0;
	s_cmd = act.argv;//ft_split(str, ' ');
	str		= s_cmd[0];
	if (pipe(p_fd) == -1)
		exit(errno);
	pid = fork();
	if (pid == -1)
		exit(errno);
	if (pid == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		printf("No builtin\n");//DEBUGEAO
		printf("%s\n", str);//DEBUGEAO
		path = get_path(str, minishell->env);
		printf("Intenta ejecutar execve\n");//DEBUGEAO
		excode = execve(path, s_cmd, minishell->env);
		if (excode == -1)
		{
			printf("Fallo execve\n");
			errno = 127;
			exit(errno);
		}
		if (excode == -1)
			exit(127);
	}
	else
	{
		if (is_builtin(str))
		{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
			printf("Builtin\n");
			execute_builtin(s_cmd, minishell);
		}
		printf("Padre espera\n");
		waitpid(pid, NULL, 0);
	}
	/*if (act.fd_in != 0)
		close(act.fd_in);
	if (act.fd_in != 1)
		close(act.fd_out);*/
	close(p_fd[0]);
	close(p_fd[1]);
}
