#include "minishell.h"

//Comprueba si un comando es un Builtin
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

//Ejecuta los builtins si los encuentra
void	execute_builtin(char **argv, t_data *shell)
{
	if (!argv || !argv[0])
		return ;
	if (ft_strcmp(argv[0], "pwd") == 0)
		execute_pwd();
	else if (ft_strcmp(argv[0], "echo") == 0)
		execute_echo(argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		execute_env(argv, shell);
	else if (ft_strcmp(argv[0], "export") == 0)
		execute_export(argv, shell);
	else if (ft_strcmp(argv[0], "unset") == 0)
		execute_unset(argv, shell);
	else if (ft_strcmp(argv[0], "cd") == 0)
		execute_cd(argv);
	else if (ft_strcmp(argv[0], "exit") == 0)
		execute_exit(argv);
	else
		ft_printf("minishell: %s: builtin no implementado\n", argv[0]);
}
