/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 10:12:20 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICKY_H
# define MICKY_H
# include "Structs.h"

# ifndef PATH_MAX
#  define PATH_MAX 512
# endif
// deberia ponerlo volatile sigatomic??
extern int	g_signal;

typedef struct s_buf
{
	char	*buff;
	int		len;
}	t_buf;

typedef struct s_expan
{
	t_data		*dt;
	t_buf		buf;
	const char	*str;
	int			i;
	char		q;
}	t_expan;

typedef struct s_hdexp
{
	t_data		*dt;
	const char	*s;
	int			i;
	char		*out;
	int			len;
}	t_hdexp;

// principal	
int			mshell(t_data *data);
// actions_utils
void		free_actions(t_data *d);
int			count_pipes(t_token **tokens);
void		init_action(t_action *act, int index);

// token _utils
void		free_token(char ***token, int nt);
const char	*skip_and_move(const char *p, int count);
int			is_meta(char c, char in_q);
const char	*scan_word(const char *p, size_t *raw, int *err);
//signals
void		setup_signals(void);
void		free_actions(t_data *d);
int			ft_actions(t_data *dt);
// token syntax
void		free_token(char ***token, int nt);
int			is_ext_comm_sim(char *command);
int			ft_syntax(t_data *dt, char ***tokens, int ntoken);
int			get_com_built(char *s);
char		*eval_expan(t_data *dt, const char *token_str);
// tools;
char		*search_env(t_data *dt, const char *var_name);
char		*strndup_safe(const char *s, size_t n);
const char	*skip_espace(const char *str);
//expan_utils
int			append_to_buff(char **dst, int *curlen, const char *src, int slen);
char		*get_var_value(t_data *dt, const char *var_name);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int			extract_var_name_len(const char *str);

#endif