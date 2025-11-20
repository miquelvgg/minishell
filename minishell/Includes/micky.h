#ifndef MICKY_H
# define MICKY_H

#include "minishell.h"

// Tipos de token 
/*
typedef enum en_token
{
	T_GENERAL,
	T_CMD,      
	T_PIPE,     
	T_RDIR_IN, 
	T_RDIR_OUT,
	T_APPEND  ,
	T_HERDOC    
}	typn_token;
*/

// estructura de datos 
typedef struct sn_token
{
	int index;      
	char *data;           
	int type;             
//	struct s_token *next; 
} tn_token;

typedef struct sn_mshell
{
	tn_token *tokens;
	char **env;       
}tn_mshell;


typedef struct	sn_data
{
	int			signal_status;
	tn_token	**token;
	char		*user_input;
	char		**env;
	char		**argv;
	char		*working_dir;
	char		*old_working_dir;
//	t_command	*cmd;
	
}	tn_data;


void free_token(char ***token, int nt);
int is_ext_comm_sim(char *command);
#ifdef  M_EXTER_FUNC
	int is_external_command(char *command);
#endif	
	int ft_syntax(tn_data *dt, char ***tokens, int ntoken);

int get_com_built(char  *s);

#endif
