/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 10:12:20 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"
// Macros

// Definiciones de funciones del proyecto

// signal
//void unblock_signal(int signal);
//void block_signal(int signal);
void	sigint_handler(int signal);
void	set_signal_action(void);
// Comprovadores de definiciones
int		ft_isblank(int c);
int		ft_ismeta(int c);
int		ft_isspace(int c);
int		is_controlop(char *str);
int		is_filename(const char *s);
int		is_redop(char *str);
int		is_token(char *str);
int		is_word(char *s);

// Builtins
void	execute_builtin(char **argv, t_data *shell);
int		is_builtin(char *cmd);
void	execute_env(char **argv, t_data *shell);
void	execute_echo(char **argv, t_data *shell);
int		is_valid_identifier(char *str);
void	execute_exit(char **argv, t_data *shell);
void	execute_export(char **argv, t_data *shell);
void	execute_pwd(t_data *shell);
void	execute_cd(char **argv, t_data *shell);
void	execute_unset(char **argv, t_data *shell);
int		is_valid_identifier(char *str);
int		is_valid_number(char *str);
int		process_export_arg(char *arg, t_data *shell);
char	**create_new_env(t_data *shell, int skip_idx, int count);

// Env
void	set_env_var(t_data *shell, char *var_assignment);
void	unset_env_var(t_data *shell, char *var_name);
int		find_env_var(char **envp, const char *name, int name_len);
void	add_env_var(t_data *shell, char *var_assignment);

//  PARSER & TOKEN
int		count_tokens_and_validate(t_data *data, const char *line);
int		shell_tokenize(t_data *data, const char *line, char ***tokens);
// PARSER
// execution.c
int		check_execution(t_data *data, int argc, char **argv);
// Pipex
typedef signed int	t_pid;
char	*getenvar(char *name, char **env);
char	*my_getenv(char *name, char **env);
void	cierra(int in, int out);
void	finish(int error);
void	ft_free_pointstring(char **tab);
void	doblefree(char **a, char **b);
int		checkacces(char **s_cmd, char **allpath, char **exec);
int		notempty(char **a, char **b);

// interactive
void	reset_prompt(int signo);
void	exect_interactive(t_data *data);
// noninteractive
void	exectscript(t_data *data);
// void	exect_noninteractive(t_data *data, int argc, char **argv);
void	non_interactive(t_data *data, int argc, char **argv);

// TERMINATOR
int		exit_var(t_data *data);

#endif
