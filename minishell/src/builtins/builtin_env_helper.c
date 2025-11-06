/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdellaza <rdellaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:15:00 by rdellaza          #+#    #+#             */
/*   Updated: 2025/10/31 16:15:00 by rdellaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/minishell.h"

/**
 * @brief Prints invalid identifier error message
 * @param arg The invalid argument string
 */
void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

/**
 * @brief Processes a single export argument
 * @param arg The argument to process (VAR or VAR=value)
 * @param shell Minishell structure
 * @return 1 if error occurred, 0 if successful
 */
int	process_export_arg(char *arg, t_minishell *shell)
{
	if (!is_valid_identifier(arg))
	{
		print_export_error(arg);
		return (1);
	}
	if (ft_strchr(arg, '='))
	{
		set_env_var(shell, arg);
	}
	return (0);
}

/**
 * @brief Processes all export arguments in a loop
 * @param argv Command arguments array
 * @param shell Minishell structure
 * @return Exit status (1 if any errors, 0 if all successful)
 */
int	process_export_args(char **argv, t_minishell *shell)
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
