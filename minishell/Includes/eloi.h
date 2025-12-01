#include "Structs.h"

char	*get_path(char *cmd, char**env);
int		is_builtin(char*cmd);
int		ft_stringlen(char**str);
void	exec(char *cmd, char **env);
char	**create_first_env(char**environ, t_data*shell);
int		initfdi(t_data*shell, char*str);
int		initfdo(t_data*shell, char*str);
int		initfdoa(t_data*shell, char*str);
int		checkinput(char *path);
int		checkoutput(char *path);
int		checkoutappend(char *path);
void	selexecute(t_data *shell);
void	heredoc(t_token *hdoc);
void	executecomand(t_data *minishell, char *str);
void	executebuiltin(t_data *minishell, char *str);
