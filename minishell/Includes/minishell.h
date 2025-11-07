#ifndef MINISHELL_H
# define MINISHELL_H

// Includes
# include "includes.h"

// Macros
# define	TRUE 1
# define	FALSE 0
# define 	READLINE_MSG "\033[1;36mshell\033[34m$> \033[0m"
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Tipos de token 
typedef enum e_token
{
	T_GENERAL,
	T_CMD,      
	T_PIPE,     
	T_RDIR_IN, 
	T_RDIR_OUT,
	T_APPEND    
}	typ_token;

// estructura de datos 
typedef struct s_token
{
	int index;      
	char *data;           
	int type;             
	struct s_token *next; 
} t_token;

typedef struct s_mshell
{
	t_token *tokens;
	char **env;       
}t_mshell;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// deberia ponerlo volatile sigatomic??
extern int	g_status;

// Data structures
typedef struct	s_data
{
	int 		is_interactive;
	int			signal_status;
	t_token		*token;
	char		*user_input;
	char		**env;

	char		*working_dir;
	char		*old_working_dir;
//	t_command	*cmd;
	
}	t_data;

//Definiciones de funciones del proyecto

//signal
void unblock_signal(int signal);
void block_signal(int signal);
void sigint_handler(int signal);
void set_signal_action(void);
//
void ft_exit(void);

//Comprovadores de definiciones
int	ft_isblank(int c);
int	ft_ismeta(int c);
int	ft_isspace(int c);
int	is_controlop(char *str);
int	is_filename(const char *s);
int	is_redop(char *str);
int	is_token(char *str);
int	is_word(char *s);

//Builtins
void	enver(char**environ);

// PARSER
// execution.c
int		check_execution(t_data *data, int argc, char **argv);
// parse_input.c
void	parse_input();

//Pipex
typedef signed int	t_pid;
char	*getenvar(char *name, char **env);
char	*my_getenv(char *name, char **env);
void	cierra(int in, int out);
void	finish(int error);
void	ft_free_pointstring(char **tab);
void	doblefree(char **a, char **b);
int		checkacces(char **s_cmd, char **allpath, char **exec);
int		notempty(char **a, char **b);

// EXECUTE
void	execute(t_data *minishell);
// interactive
void	reset_prompt(int signo);
void	exect_interactive(t_data *data);
// noninteractive
void	exectscript(t_data *data);
//void	exect_noninteractive(t_data *data, int argc, char **argv);
void	non_interactive(t_data *data, int argc, char **argv);

// TERMINATOR
void	free_data();
void	exit_shelly();

#endif
