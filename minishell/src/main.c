#include "minishell.h"

int mshell(t_data	*data)
{
	int salir;
	char *line;

	//(void)data;
	data->signal_status = 0;
	salir = 0;
	block_signal(SIGQUIT);
	block_signal(SIGINT);
  	
	using_history();     //initialize history 
	while (!salir)	
	{
		line = readline(READLINE_MSG);
	    if (line[0] == 'x')
	    {
	    	salir = 1;
	    }
		 if (*line) 
		 {
			add_history(line);
		 }
	    	
		free(line);    
	}
   	unblock_signal(SIGINT);
	unblock_signal(SIGQUIT);
	return(0);
}


/* definir errores de salida */

int main(int argc, char **argv)
{
	t_data	data;
	int		res;

	if (argc != 1)
		return(1);
	
	// guardar valores de 	extern char **environ;
	

	ft_memset(&data, 0, sizeof(t_data));
	res	= mshell(&data);

	if (!check_execution(&data, argc, argv))
		ft_exit();
	if (data.is_interactive)
		exect_interactive(&data);
//	else
//		exect_noninteractive(&data, argc, argv);//temporal, hasta que rellenemos el data en checkexecution
//	exit_shelly(&data);
	return (0);
}
