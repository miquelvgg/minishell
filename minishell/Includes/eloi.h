/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eloi.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:20:38 by epascual          #+#    #+#             */
/*   Updated: 2025/12/31 14:56:26 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Structs.h"

void	print_env(t_data*data);
char	*get_path(char *cmd, char**env);
int		is_builtin(char*cmd);
int		ft_stringlen(char**str);
void	exec(char *cmd, char **env);
char	**create_first_env(char**environ);
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
void	prt_error(char *arg);
void	print_findfile_error(char *arg);
//exacti_util.c 
void	existcmd(char *cmd);
void	is_exec(char *cmd);
void	is_dir(char *cmd);
void	ft_nopath(void);
char	*my_getenv(char *name, char **env);
//exacti_ext.c
void	ft_free_pointstring(char **tab);
char	*ft_nfstrjoin(char const *s1, char const *s2);
char	*get_path(char *cmd, char **env);
int		redir_in_parent(t_action *act);
int		redir_out_parent(t_action *act);
//exacti_exec.c
void	directexec(t_action act, t_data*minishell);
void	executep(t_action act, t_data*minishell);
void	exactionp(t_action act, t_data *data);
// heredoc

int		ft_prepare_heredocs(t_data *data);
void	ft_close_heredocs(t_data *data);
pid_t	hd_fork_reader(int fd, t_data *data, t_action *act);
char	*hd_expand_line(t_data *data, const char *line);
char	*hd_env_value(char **env, const char *name, int nlen);
