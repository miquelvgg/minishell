#ifndef STRUCT_H
# define STRUCT_H
// Macros
# define	TRUE 1
# define	FALSE 0
# define 	READLINE_MSG "\033[1;36mshell\033[34m$> \033[0m"

typedef enum e_redir
{	
	R_NULL,
	R_INPUT,  
	R_OUTPUT,  
	R_APPEND,
	R_HEREDOC 
} typ_redir;

// Tipos de token 
typedef enum e_token
{
	T_GENERAL,
	T_CMD,      
	T_PIPE,     
	T_RDIR_IN, 
	T_RDIR_OUT,
	T_APPEND ,
	T_HERDOC  
}	typ_token;

// estructura de datos 
typedef struct s_token
{
	int index;      
	char *data;           
	int type;             
	//struct s_token *next; 
} t_token;

#define METACHARED "|<>"
#define FORBDDEN "&\\"


// deberia ponerlo volatile sigatomic??
extern int	g_status;


typedef struct s_action
{
	int		index;
	char	**argv;
	char	*infile;
	char	*outfile;
	int		append; // 0 = reescribir  (>), 1 = abrir (>>)
	int		fd_in;
	int		fd_out;
} t_action;


// Data structures
typedef struct	s_data
{
	int				signal_status;
	t_token			**token;
	t_action		*actions;
	int				n_actions;
	int				fdin;
	int				fint;
	int				fdout;
	char			*user_input;
	char			**env;
	char			**argv;
	char			*working_dir;
	char			*old_working_dir;
	int				**pipes;
	unsigned char	xstatus;

}	t_data;
#endif
