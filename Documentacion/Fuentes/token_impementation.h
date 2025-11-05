








typedef enum e_ast_type
{
	AST_NONE = 0;
	AST_COMAND; 
	AST_PIPE;
	AST_AND;
	AST_OR;
	AST_REDIRECT;
	// AST_HERE_DOC;

} t_ast_type

typedef union u_data
{
	struct s_command_node;
	struct s_pipe_node;
	struct s_and_node;
	struct s_or_node;
	struct s_redirect_node;
	// struct s_here_doc_node;
						
} t_data


typedef struct s_ast_node
{
	t_ast_type id;
	union t_data;
	struct s_ast_node *left;
	struct s_ast_node *right;
} t_ast_node;





ft_size(e_ast_type id)
{


}


