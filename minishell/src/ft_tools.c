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


/*Nombre de expansion $name */
// Manejo especial de "$?" (codigo de salida del ultimo comando)
// Si no es un nombre valido  0.
int	extract_var_name_len(const char *s)
{
	int	len;

	len = 0;
	
	if (s[len] == '_' || isalpha((unsigned char)s[len])) /*caracteres permitidos*/
	{
		while (s[len] && (isalnum((unsigned char)s[len]) || s[len] == '_'))
			len++;
	}
	else if (s[len] == '?')
		len++;
	return (len);
}