#include "minishell.h"

const char *skip_espace(const char *str) {
    while (*str && isspace((unsigned char)*str)) {
        str++;
    }
    return str;
}

// Helper: Crea un duplicado de una porción de string
char *strndup_safe(const char *s, size_t n) {
    char *p = (char *)malloc(n + 1);
    if (p == NULL) return NULL;
    strncpy(p, s, n);
    p[n] = '\0';
    return p;
}
// control de comillas
char *quotation_marks(char *input, int  *count, int  *ret)
{
	char quote_type = 0;
	
	*ret = 0;
    if (*input == '\'' || *input == '\"') 
	{
        quote_type = *input;
        input++; // Saltar comilla de apertura
        // Buscar comilla de cierre del mismo tipo
        while (*input && *input != quote_type) {
            input++;
        }
        // VALIDAR CIERRE
        if (!*input) {
            fprintf(stderr, "Error: Comillas %c sin cerrar.\n", quote_type);
            *ret =-1;
            return NULL;
        }
        input++; // Saltar comilla de cierre
        *count=*count+1;
        input =(char *) skip_espace((const char *)input);
        *ret =1;
		return (input);
    }
	return (input);
}


int count_tokens_and_validate(const char *line) 
{
    int count = 0;
	int ret = 0;
    const char *input = line;

	if (!line || *line == '\0') 
        return 0;	
    
    input = skip_espace(input);	

    while (*input) {

        if (strchr(FORBDDEN, *input))
        {
            fprintf(stderr, "Error: caracter %c \n", *input);
            return (-2);
        }
        if (strchr(METACHARED, *input)) {
            count++;
            if (strchr("<>", *input) && *(input + 1) == *input) {
                input += 2;
            } else {
                input += 1;
            }
            input = skip_espace(input);
            continue;
        }
		input = quotation_marks((char *)input, &count, &ret);
		
		if (ret)
		{
			if (ret < 0)
				return (-1);
			else 
				continue;
		}
        while (*input && !isspace((unsigned char)*input) && !strchr(METACHARED, *input)) {
            input++;
        }
        count++;
        input = skip_espace(input);
    }
    return count;
}

int shell_tokenize(const char *line, char ***tokens) {
    // 1. Contar tokens y validar comillas
    int num_tokens = count_tokens_and_validate(line);
    
    if (num_tokens < 0) {
        *tokens = NULL;
        return -1; // Error de comillas sin cerrar
    }
    if (num_tokens == 0) {
        *tokens = NULL;
        return 0; // Línea vacía
    }

    // 2. Asignación de memoria exacta (num_tokens + 1 para el terminador NULL)
    char **token_list = (char **)malloc(sizeof(char *) * (num_tokens + 1));
    if (!token_list) {
        perror("Fallo de malloc para token_list");
        *tokens = NULL;
        return -1;
    }

    // 3. Rellenar el array de tokens (La lógica es la misma que la función de conteo)
    char *input = (char *)line;
    int current_token = 0;
    
    input = (char *)skip_espace(input);

    while (*input) {
        // La lógica de cálculo de 'token_len' es idéntica a 'count_tokens_and_validate'
        // Simplemente copiamos la porción de string en lugar de solo contar.
        
        // [CÓDIGO DE CÁLCULO DE token_len y quote_type (omitido por espacio, pero debe ser el mismo que el contador)]
        
        int token_len = 0;
        char quote_type = 0;
        int is_metachar = 0;
        char *token_start = input;

        if (strchr(METACHARED, *input)) {
            is_metachar = 1;
            token_len = 1; 
            if (strchr("<>", *input) && *(input + 1) == *input) token_len = 2;
        }
        else {
            if (*input == '\'' || *input == '\"') {
                quote_type = *input;
                input++; 
                token_len++;
            }
            while (*(input + token_len)) 
            {
                if (quote_type) 
                {
                    if (*(input + token_len) == quote_type) 
                    {
                        token_len++;
                        break;
                    }
                } 
                else if (isspace((unsigned char)*(input + token_len)) || strchr(METACHARED, *(input + token_len))) {
                    break; 
                }
                token_len++;
            }
        }
        
        // 4. Almacenar el Token
        token_list[current_token] = strndup_safe(token_start, token_len);
        if (!token_list[current_token]) {
            // Fallo de malloc en strndup, requiere liberar tokens anteriores
            for (int i = 0; i < current_token; i++) free(token_list[i]);
            free(token_list);
            *tokens = NULL;
            return -1; 
        }
        current_token++;

        // 5. Mover y limpiar
        input += token_len;
        if (!is_metachar && quote_type) input--;
        input = (char *)skip_espace(input);
    }
    
    // 6. Terminar con NULL
    token_list[num_tokens] = NULL;
    *tokens = token_list;
    return num_tokens;
}


