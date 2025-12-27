#include "minishell.h"

//Comprueba el tamanyo de char**str
int	ft_stringlen(char**str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

//Intercambia dos posiciones del char**str
static void	ft_swapenv(char **swap, int i, int j)
{
	char *tmp;

	if (!swap[i] || !swap[j])
		return ;
	tmp = swap[i];
	swap[i] = swap[j];
	swap[j] = tmp;
}

//Ordena Alfabeticamente el char**
static void	ft_sortpstr(char***envp)
{
	char**env;
	int i;
	int j;
	int	c;
	int m;

	env = *envp;
	m = ft_stringlen(env) - 1;
	i = 0;
	while (i < m)
	{
		j = 0;
		while (j < m)
		{
			if (env[j])
			{
			c = 0;
			while (env[j][c] == env[j +1][c])
				c++;
			if (env[j][c] > env[j +1][c])
				ft_swapenv(env, j, j +1);
			}
			j++;
		}
		i++;
	}
}

//Export builtin sin argumentos
static void	export_print_all(t_data *shell)
{
	int	i;
	int max;
	char **envtemp;

	i = 0;
	max = ft_stringlen(shell->env);
	if (max != 0)
	{
	envtemp = create_new_env(shell, -1, ft_stringlen(shell->env));
	ft_sortpstr(&envtemp);
	while (i < max)
	{
		printf("declare -x %s\n", envtemp[i]);
		i++;
	}
	free(envtemp);
	}
}

/*main de prueba de export sin args
int	main(int a, char**av, char**env)
{
	export_print_all(env);
	return (0i);
}*/

//Imprime el error de invalid identifier
static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

//Procesa un export de valor unico
int	process_export_arg(char *arg, t_data *shell)
{
	if (!is_valid_identifier(arg))
	{
		print_export_error(arg);
		return (1);
	}
	if (ft_strchr(arg, '='))
		set_env_var(shell, arg);
	return (0);
}

//Procesa export con varios argumentos
static int	process_export_args(char **argv, t_data *shell)
{
	int	i;
	int	has_error;

	has_error = 0;
	i = 1;
	while (argv[i])
	{
		if (process_export_arg(argv[i], shell))
			has_error = 1;
		i++;
	}
	if (has_error)
		return (1);
	return (0);
}

//Export builtin
void	execute_export(char **argv, t_data *shell)
{
	if (!argv[1])
	{
		export_print_all(shell);
		shell->xstatus = 0;
		return ;
	}
	shell->xstatus = process_export_args(argv, shell);
}
