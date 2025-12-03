#include "minishell.h"

size_t	ft_strncpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	if (src == NULL)
		return (0);
	len = 0;
	while (src[len] != '\0')
		len++;
	if (size == 0)
		return (len);
	i = 0;
	while (src[i] != '\0' && i < size )
	{
		dst[i] = src[i];
		i++;
	}
	return (len);
}


void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	// Caso 1: Si new_size es 0, liberar ptr y retornar NULL. Actúa como free(ptr).
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	// Caso 2: Si ptr es NULL, retornar el resultado de malloc(new_size). Actúa como malloc(new_size).
	if (ptr == NULL)
		return (malloc(new_size));
	
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL); 

	//cuántos bytes hay que copiar
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;

	memcpy(new_ptr, ptr, copy_size);

	free(ptr);

	return (new_ptr);
}

char	*get_var_value(const char *var_name)
{
	if (!var_name || *var_name == '\0')
		return (NULL);
	if (var_name[0] == '?' && var_name[1] == '\0')
		return (NULL); //el ultimo  status (exit)
	
	return (getenv(var_name)); // O tu propia lista de env
}



int	append_to_buffer(char **dst, int *current_len, const char *src, int src_len)
{
	int		new_len;
	char	*new_dst;

	if (src_len <= 0)
		return (1);
	new_len = *current_len + src_len;
	new_dst = (char *)ft_realloc(*dst,*current_len, (new_len + 1) * sizeof(char));
	if (!new_dst)
		return (0); // Fallo de realloc
	*dst = new_dst;
	//strncpy(*dst + *current_len, src, src_len);
	ft_strncpy(*dst + *current_len, src, src_len);
	(*dst)[new_len] = '\0';
	*current_len = new_len;
	return (1);
}

// tenemos de pasar (g_last_status $? )
/* simplificar y no hacerlo caracter por caracter  */
char	*eval_expan(const char *token_str)
{
	char	*expanded_token;
	int		len;
	char	quote_state; // 0: none, '\'': simple, '"': double
	int		i;
	int		var_name_len;
	char	*var_name;
	char	*var_value;
	char	*status_str;
	int		g_last_status;

	g_last_status =0;
	expanded_token = (char *)malloc(1);
	if (!expanded_token)
		return (NULL);
	expanded_token[0] = '\0';
	len = 0;
	quote_state = 0;
	i = 0;
	while (token_str[i] != '\0')
	{
		if (token_str[i] == '\'' || token_str[i] == '"')
		{
			if (quote_state == 0)
			{
				/*  comillas */
				quote_state = token_str[i];
				i++;
				continue ;
			}
			else if (quote_state == token_str[i])
			{
				/* Salir de comillas */
				quote_state = 0;
				i++;
				continue ;
			}
		}
		/* 2. expansion de $ tiene en cuenta no expande comillas simples*/
		if (token_str[i] == '$' && quote_state != '\'')
		{
			i++; /* Saltar '$' */
			var_name_len = extract_var_name_len(&token_str[i]);
			if (var_name_len > 0)
			{
				var_name = strndup_safe(&token_str[i], var_name_len);
				if (!var_name)
				{
					free(expanded_token);
					return (NULL);
				}
				/* Caso especial: $? */
				if (var_name[0] == '?' && var_name[1] == '\0')
				{
					status_str = ft_itoa(g_last_status);
					if (!status_str)
					{
						free(var_name);
						free(expanded_token);
						return (NULL);
					}
					if (!append_to_buffer(&expanded_token, &len,
							status_str, ft_strlen(status_str)))
					{
						free(status_str);
						free(var_name);
						free(expanded_token);
						return (NULL);
					}
					free(status_str);
				}
				else
				{
					/* Variable de entorno normal */
					var_value = get_var_value(var_name);
					if (var_value)
					{
						if (!append_to_buffer(&expanded_token, &len,var_value, ft_strlen(var_value)))
						{
							free(var_name);
							free(expanded_token);
							return (NULL);
						}
					}
				}
				free(var_name);
				i += var_name_len;
				continue ;
			}
			/* No hay nombre de variable válido → '$' literal */
			if (!append_to_buffer(&expanded_token, &len, "$", 1))
			{
				free(expanded_token);
				return (NULL);
			}
			/* OJO: no incrementamos i aquí; procesaremos el carácter actual en la siguiente vuelta */
			continue ;
		}

		/* 3. Carácter literal */
		
		if (!append_to_buffer(&expanded_token, &len, &token_str[i], 1))
		{
			free(expanded_token);
			return (NULL);
		}
		i++;
	}
	return (expanded_token);
}
