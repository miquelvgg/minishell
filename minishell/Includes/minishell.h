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

#define METACHARED "|<>"
#define FORBDDEN "&\\"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// deberia ponerlo volatile sigatomic??
extern int	g_status;

// Data structures
typedef struct	s_data
{
	int			signal_status;
	t_token		*token;
	char		*user_input;
	char		**env;
	char		**argv;
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
void	execute_builtin(char**argv, t_data *shell);
int		is_builtin(char *cmd);
void	execute_env(char **argv, t_data *shell);
void	execute_echo(char **argv);
int		is_valid_identifier(char *str);
void	execute_exit(char **argv);
void	execute_export(char **argv, t_data *shell);
void	execute_pwd();
void	execute_cd(char **argv);
void	execute_unset(char **argv, t_data *shell);
int		is_valid_identifier(char *str);
int		is_valid_number(char *str);
int		process_export_arg(char *arg, t_data *shell);
char	**create_new_env(t_data *shell, int skip_idx, int count);

//Env
void	set_env_var(t_data *shell, char *var_assignment);
void	unset_env_var(t_data *shell, char *var_name);
int		find_env_var(char **envp, const char *name, int name_len);
void	add_env_var(t_data *shell, char *var_assignment);

//  PARSER & TOKEN
	int count_tokens_and_validate(const char *line) ;
	int shell_tokenize(const char *line, char ***tokens);
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
