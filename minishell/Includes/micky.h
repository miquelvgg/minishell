#ifndef MICKY_H
# define MICKY_H

extern int	g_signal;

#include "Structs.h"

#ifndef PATH_MAX
	#define 	PATH_MAX   512
#endif


typedef struct s_buf
{
	char	*buff;
	int		len;
}	t_buf;
// q = es caracter de  comillas 
typedef struct s_expan
{
	t_data		*dt;
	t_buf		buf;
	const char	*str;
	int			i;
	char		q;
}	t_expan;

void	setup_signals(void);
void free_actions(t_data *d);
int ft_actions(t_data *dt);

void free_token(char ***token, int nt);
int is_ext_comm_sim(char *command);
int ft_syntax(t_data *dt, char ***tokens, int ntoken);
int get_com_built(char  *s);

char	*eval_expan(t_data *dt,const char *token_str);
// tools;
char *search_env(t_data *dt,const char *var_name );
char 		*strndup_safe(const char *s, size_t n);
const char *skip_espace(const char *str);
//expan_utils

int append_to_buffer(char **dst, int *curr_len, const char *src,int src_len);
char	*get_var_value(t_data *dt, const char *var_name);
void *ft_realloc(void *ptr, size_t old_size, size_t new_size);
int extract_var_name_len(const char *str);

#endif