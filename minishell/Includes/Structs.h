/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 10:12:20 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// Macros
# define TRUE 1
# define FALSE 0
# define READLINE_MSG "\033[1;36mshell\033[34m$> \033[0m"
# define METACHARED "|<>"
# define FORBDDEN "&\\"

typedef enum e_redir
{
	R_NULL,
	R_INPUT,
	R_OUTPUT,
	R_APPEND,
	R_HEREDOC
}	t_redir;

// Tipos de token 
typedef enum e_tiptoken
{
	T_GENERAL,
	T_CMD,
	T_PIPE,
	T_RDIR_IN,
	T_RDIR_OUT,
	T_APPEND ,
	T_HERDOC
}	t_tiptoken;
// estructura de datos 
typedef struct s_token
{
	int		index;
	char	*data;
	int		type;
}	t_token;

typedef struct s_action
{
	int		index;
	char	**argv;
	char	*infile;
	char	*outfile;
	int		append;
	int		fd_in;
	int		fd_out;
}	t_action;

// Data structures
typedef struct s_data
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
