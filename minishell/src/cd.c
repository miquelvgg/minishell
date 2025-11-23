#include "minishell.h"

//Comprueba los argumentos del cd
static int	check_cd_args(char **argv)
{
	if (argv[1] && argv[2])
	{
		ft_printf("minishell: cd: too many arguments\n");
		errno = 1;
		return (1);
	}
	return (0);
}

//Obtiene el path del directorio al que cambiar
//Si no esta la env HOME falla
static char	*get_cd_target_path(char **argv)
{
	char	*path;

	if (!argv[1] || ft_strncmp(argv[1], "~", 2) == 0)
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_printf("minishell: cd: HOME not set\n");
			errno = 1;
			return (NULL);
		}
		return (path);
	}
	return (argv[1]);
}

//Intenta cambiar el directorio y muestra error si falla
static int	change_directory(char *path)
{
	if (chdir(path) == -1)
	{
		ft_printf("minishell: cd: %s: ", path);
		perror("");
		errno = 1;
		return (1);
	}
	errno = 0;
	return (0);
}

//Ejecuta el cd con sus comprovaciones
void	execute_cd(char **argv)
{
	char	*path;
	char	old_pwd[PATH_MAX];

	if (check_cd_args(argv))
		return ;
	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		perror("minishell: cd: getcwd");
		errno = 1;
		return ;
	}
	path = get_cd_target_path(argv);
	if (!path)
		return ;
	change_directory(path);
}
