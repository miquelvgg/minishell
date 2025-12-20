#include "minishell.h"

void free_token(char ***token, int nt)
{
	int i;
	char **mtoken;
	
	i = 0;
	if ((!token) ||(*token == NULL))
		return ;
	mtoken = *token;


	while ((mtoken[i] != NULL ) &&(i < nt))
	{
        
		free(mtoken[i]);
        mtoken[i] =NULL;
		i++;
	}

	free(mtoken);
    mtoken = NULL;
}

static const char *scan_word(const char *p, size_t *raw_len, size_t *unz_len, int *err_uc)
{
    const char *s = p;
    char 		in_q;            /* 0=no, '\"' si dentro de comillas */
    size_t 		raw = 0; 
    size_t 		unz = 0;
    char c;

    while (s[raw]) {
        c = s[raw];
        if (c == in_q )
        {          
                in_q= 0;
                
                raw++;                 
                continue;
        }
        /* caracter considerado normal si hay unas comillas abiertas da igual  fin de palabra si espacio o metachar */   
        if (isspace((unsigned char)c) || ft_strchr(METACHARED, c)) 
        	break;
        if (c == '\'' )
        {  /* apertura de comillas */
            in_q = c;
            raw++;                     /* comilla no cuenta en unz */
            continue;
        }
        else if (c == '\"' ) 
        {
            in_q= c;
            raw++;                     /* comilla no cuenta en unz */
            continue;
        }
        /* carácter normal */
        raw++;
        unz++;
    }
    if (in_q) 
    {               /* comilla sin cerrar */
        if (err_uc) 
    	{
           	*err_uc = 1;
        }
    } else 
    {
        if (err_uc) 
    	{
        	*err_uc = 0;
    	}
    }   
	if (raw_len) *raw_len = raw;
    if (unz_len) *unz_len = unz;
	return s + raw;
}



/* Copia una palabra sin comillas (longitud descomillada conocida) */
static void copy_unquoted(char *dst, const char *src, size_t raw_len)
{
    size_t i =0;
    size_t j = 0;
//    char in_q = 0;
// char c


    while ((src[i])&&(i < raw_len))
    {
      dst[j] =  src[i];
      j++;
      i++;
    }

 /* while ((src[i])&&(i < raw_len))
     {
     c = src[i];
      if (in_q) 
        {
            if (c == in_q) 
            { 
            	in_q = 0; 
	            continue; 
            } 
            dst[j++] = c;
        } 
        else 
        {
                if (c == '\'' || c == '\"') {
                    in_q = c; 
                    continue; 
                    } 
            dst[j++] = c;
        }
        i++;    
    }
*/
    dst[j] = '\0';
}

/* -------- contador corregido -------- */
int count_tokens_and_validate(const char *line)
{
    int count = 0;
    const char *p;

    if (!line) return 0;
    p = skip_espace(line);

    while (*p) {
        /* prohibidos “sueltos” */
        if (strchr(FORBDDEN, *p)) {
            fprintf(stderr, "Error: caracter %c\n", *p);
            return -2;
        }

        /* metacaracteres (1 ó 2) */
        if (strchr(METACHARED, *p)) {
            count++;
            if ((*p == '<' || *p == '>') && *(p + 1) == *p) p += 2;
            else p += 1;
            p = skip_espace(p);
            continue;
        }

        /* palabra (con o sin comillas) */
        size_t raw_len, unz_len;
        int err_uc;
        const char *end = scan_word(p, &raw_len, &unz_len, &err_uc);
        if (err_uc) {
            fprintf(stderr, "Error1: Comillas sin cerrar.\n");
            return -1;
        }
        if (raw_len == 0) {   /* debería no ocurrir, pero por seguridad */
            p++;
            continue;
        }
        count++;
        p = skip_espace(end);
    }
    return count;
}

/* -------- tokenizador  -------- */
/* line --> tokens */
int shell_tokenize(const char *line, char ***tokens)
{
    int num_tokens; 
    int k;
    int len;
    const char *p;
    char **v;

    /* palabra */
    size_t raw_len; 
    size_t unz_len;
    int err_uc;
    const char *end;

    end = NULL;
    num_tokens = count_tokens_and_validate(line);

    if (num_tokens < 0) 
    {
        *tokens = NULL;
        return -1;
    }
    if (num_tokens == 0) 
    {
        *tokens = NULL;
        return 0;
    }
    v = (char **)malloc(sizeof(char *) * (num_tokens + 1));
    if (!v) {
        perror("malloc token_list");
        *tokens = NULL;
        return -1;
    }
    p = skip_espace(line);
    k = 0;
    while (*p) {
        if (ft_strchr(METACHARED, *p)) 
        {
            len = 1;
            if ((*p == '<' || *p == '>') && *(p + 1) == *p)  //">> or <<"
                len = 2;
            v[k] = strndup_safe(p, (size_t)len);
            if (!v[k]) 
            {          
                printf("Error (malloc)\n");              
                free_token(&v,k);
                return (-1);
            }
            k++;
            p += len;
            p = skip_espace(p);
            continue;
        }

        end = scan_word(p, &raw_len, &unz_len, &err_uc);
        
        if (err_uc) { /* no debería pasar por el validador previo, pero por si acaso */
            fprintf(stderr, "Error2: Comillas sin cerrar.\n");
            printf("Error\n");
            //goto fail;
            free_token(&v,k);
            return (-1);
        }

        /* reservar y copiar con comillas*/
        //v[k] = (char *)malloc(unz_len + 1);
        v[k] = (char *)malloc(raw_len + 1);
        if (!v[k]) 
        {
            free_token(&v,k);
            return (-1);
        }

            //goto oom;
        //printf("1 len :%lu -->%lu\n",raw_len,unz_len);
        copy_unquoted (v[k], p, raw_len);
        k++;
        p = skip_espace(end);
    }

    v[k] = NULL;
    *tokens = v;
    return k;
}
