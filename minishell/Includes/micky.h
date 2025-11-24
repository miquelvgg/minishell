#ifndef MICKY_H
# define MICKY_H

#include "Structs.h"

#ifndef PATH_MAX
	#define 	PATH_MAX   512
#endif

void free_token(char ***token, int nt);
int is_ext_comm_sim(char *command);
int ft_syntax(t_data *dt, char ***tokens, int ntoken);
int get_com_built(char  *s);

char	*eval_expan(const char *token_str);
// tools;
char *strndup_safe(const char *s, size_t n);
#endif
