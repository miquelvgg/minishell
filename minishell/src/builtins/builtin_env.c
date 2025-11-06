/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdellaza <rdellaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 09:01:46 by rdellaza          #+#    #+#             */
/*   Updated: 2025/11/02 15:30:32 by rdellaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/minishell.h"

/*
Env built-in implementation
Takes argv Command and arguments
Takes shell Minishell structure
*/
void	execute_env(char **argv, t_minishell *shell)
{
	int	i;

	(void)argv;
	i = 0;
	while (shell->envp[i])
	{
		ft_printf("%s\n", shell->envp[i]);
		i++;
	}
	shell->last_exit_status = 0;
}

/*
Export built-in implementation (first half)
*/
static void	export_print_all(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		ft_printf("declare -x %s\n", shell->envp[i]);
		i++;
	}
}

/*
Validates if a string is a valid variable identifier
Takes str String to validate (can be "VAR" or "VAR=value")
Returns 1 if valid, 0 if invalid
*/
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] == '=' && i == 0)
		return (0);
	return (1);
}

/*
Export built-in implementation (second half)
Takes argv Command and arguments
Takes shell Minishell structure
*/
void	execute_export(char **argv, t_minishell *shell)
{
	if (!argv[1])
	{
		export_print_all(shell);
		shell->last_exit_status = 0;
		return ;
	}
	shell->last_exit_status = process_export_args(argv, shell);
}

/*
Unset built-in implementation
Takes argv Command and arguments
Takes shell Minishell structure
*/
void	execute_unset(char **argv, t_minishell *shell)
{
	int	i;

	if (!argv[1])
	{
		shell->last_exit_status = 0;
		return ;
	}
	i = 1;
	while (argv[i])
	{
		unset_env_var(shell, argv[i]);
		i++;
	}
	shell->last_exit_status = 0;
}
