#include "minishell.h"

/*void	execute(t_data *minishell)
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
		if (pid == 0)
		{
			printf("Path");
			path = get_path(s_cmd[0], minishell->env);
			printf(" obtenido\n");
			excode = execve(path, s_cmd, NULL);
			printf("\npostejecutado\n");
		}
		else
		{
			printf("esperando\n");
			waitpid(pid, NULL, 0);
			printf("esperado\n");
		}
	}
	printf("liberando");
	//free(s_cmd);
	if (excode != 0)
	{
		ft_free_pointstring(s_cmd);
	}
}*/
void execute(t_data *minishell)
{
    printf("%s\n", minishell->token->data);
    char *path;
    int excode;
    char **s_cmd;
    int pid;

    excode = 0;
    s_cmd = ft_split(minishell->token->data, ' ');
    if (is_builtin(s_cmd[0]))
    {
        execute_builtin(s_cmd, minishell);
        ft_free_pointstring(s_cmd);
    }
    else
    {
        pid = fork();
        if (pid == 0)
        {
            printf("Path");
            path = get_path(s_cmd[0], minishell->env);
            printf(" obtenido\n");
            excode = execve(path, s_cmd, NULL);
            if (excode == -1)
            {
                ft_free_pointstring(s_cmd);
				errno = 1;
                exit(errno);
            }
        }
        else
        {
            printf("esperando\n");
            waitpid(pid, NULL, 0);
            printf("esperado\n");
            ft_free_pointstring(s_cmd);
        }
    }
}
