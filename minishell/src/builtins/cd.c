#include "minishell.h"

/**
 * @brief Checks if cd has too many arguments
 * @param argv Command arguments array
 * @param shell Minishell structure for error status
 * @return 1 if too many arguments, 0 otherwise
 */
int	check_cd_args(char **argv, t_minishell *shell)
{
	if (argv[1] && argv[2])
	{
		ft_printf("minishell: cd: too many arguments\n");
		shell->last_exit_status = 1;
		return (1);
	}
	return (0);
}

/**
 * @brief Gets the target directory path for cd command
 * @param argv Command arguments array
 * @param shell Minishell structure for error status
 * @return Target path string, or NULL on error
 */
char	*get_cd_target_path(char **argv, t_minishell *shell)
{
	char	*path;

	if (!argv[1] || ft_strncmp(argv[1], "~", 2) == 0)
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_printf("minishell: cd: HOME not set\n");
			shell->last_exit_status = 1;
			return (NULL);
		}
		return (path);
	}
	return (argv[1]);
}

/**
 * @brief Changes to the specified directory
 * @param path Target directory path
 * @param shell Minishell structure for error status
 * @return 0 on success, 1 on error
 */
int	change_directory(char *path, t_minishell *shell)
{
	if (chdir(path) == -1)
	{
		ft_printf("minishell: cd: %s: ", path);
		perror("");
		shell->last_exit_status = 1;
		return (1);
	}
	shell->last_exit_status = 0;
	return (0);
}

/*
		  CD built-in implementation
		  Takes argv Command and arguments
		  Takes shell Minishell structure
		  */
void	execute_cd(char **argv, t_minishell *shell)
{
	char	*path;
	char	old_pwd[PATH_MAX];

	if (check_cd_args(argv, shell))
		return ;
	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		perror("minishell: cd: getcwd");
		shell->last_exit_status = 1;
		return ;
	}
	path = get_cd_target_path(argv, shell);
	if (!path)
		return ;
	change_directory(path, shell);
}
