/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eloi.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:20:38 by epascual          #+#    #+#             */
/*   Updated: 2025/12/28 12:21:15 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Structs.h"

void	print_env(t_data*data);
char	*get_path(char *cmd, char**env);
int		is_builtin(char*cmd);
int		ft_stringlen(char**str);
void	exec(char *cmd, char **env);
char	**create_first_env(char**environ, t_data*shell);
int		initfdi(int*shell, char*str);
int		initfdo(int*shell, char*str);
int		initfdoa(int*fdoa, char*str);
int		checkinput(char *path);
int		checkoutput(char *path);
int		checkoutappend(char *path);
void	selexecute(t_data *shell);
void	heredoc(t_token *hdoc);
void	execute(t_action act, t_data*minishell);
void	executecomand(t_data *minishell, char *str);
void	executebuiltin(t_data *minishell, char *str);
void	exaction(t_action act, t_data*data);
void	exactions(t_data*data);
void	free_data_struc(t_data *dt);
void	executep(t_action act, t_data*minishell);

//pipas.c
int		initpipes(int **pipes, int size);
int		liberapipes(int **pipes, int i);
int		**mempipas(int max);
void	closepipes(t_data *data);
void	preparepipes(t_action act, t_data *data);

//envsorter
void	ft_sortpstr(char***envp);
//error
void	print_export_error(char *arg);
