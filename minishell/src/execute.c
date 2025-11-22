#include "minishell.h"

//executa un comando
void execute(t_data *minishell)
{
    //printf("%s\n", minishell->token->data);
    char *path;
    int excode;
    char **s_cmd;
    int pid;

	if (!(minishell->token->data) || !(*(minishell->token->data)))
		return ;
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
            path = get_path(s_cmd[0], minishell->env);
			dup2(minishell->fdin, 0);//activa el stdin
			dup2(minishell->fdout, 1);
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
            waitpid(pid, NULL, 0);
            ft_free_pointstring(s_cmd);
        }
    }
}
