#include "minishell.h"


const char *skip_espace(const char *str) 
{
    while (*str && ft_isspace((unsigned char)*str)) 
    	str++;
    return str;
}

char *strndup_safe(const char *s, size_t n) 
{
	char *p;
	p = (char *)malloc(n + 1);
	if (!p) 
		return NULL;
	ft_memcpy(p, s, n);
 	p[n] = '\0';
    return p;
}



char *search_env(t_data *dt,const char *var_name )
{
	int n_even;
	int len;
	
	len = ft_strlen(var_name);
	n_even =find_env_var(dt->env, var_name, len);
	if (n_even == -1)
		return(NULL);
	return(dt->env[n_even]+len+1);
}