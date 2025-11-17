#include "Structs.h"

char	*get_path(char *cmd, char**env);
int		is_builtin(char*cmd);
int		ft_stringlen(char**str);
void	exec(char *cmd, char **env);
char	**create_first_env(char**environ, t_data*shell);
