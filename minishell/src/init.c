#include "minishell.h"
// Blocks the specified signal
void block_signal(int signal)
{
	// Set of signals to block
	sigset_t sigset;

	// Initialize set to 0
	sigemptyset(&sigset);
	// Add the signal to the set
	sigaddset(&sigset, signal);
	// Add the signals in the set to the process' blocked signals
	sigprocmask(SIG_BLOCK, &sigset, NULL);
	if (signal == SIGQUIT)
	printf("\e[36mSIGQUIT (ctrl-\\) blocked.\e[0m\n");
}

// Unblocks the given signal
void unblock_signal(int signal)
{
	// Set of signals to unblock
	sigset_t sigset;

	// Initialize the set to 0
	sigemptyset(&sigset);
	// Add the signal to the set
	sigaddset(&sigset, signal);
	// Remove set signals from the process' blocked signals
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
	if (signal == SIGQUIT)
		printf("\e[36mSIGQUIT mvs(ctrl-\\) unblocked.\e[0m\n");
}
void sigint_handler(int signal)
{
 if (signal != SIGINT)
  return ;
// Blocks other SIGINT signals to protect the global
// variable during access
	block_signal(SIGINT);
//	g_unblock_sigquit = 1;  	//mvs variable global 
	unblock_signal(SIGINT);
}

	

void set_signal_action(void)
{
	// Declare sigaction structure
	struct sigaction act;

	// Initialize structure to 0.
	bzero(&act, sizeof(act));
	// Add new signal handler
	act.sa_handler = &sigint_handler;
	// Apply new signal handler to SIGINT (ctrl-c)
	sigaction(SIGINT, &act, NULL);
}

void manejador_sigint(int signum) 
{
    printf("\nSeñal SIGINT (%d) recibida. Ignorando...\n", signum);
    // Se puede realizar alguna limpieza o guardar datos aquí
}


void  print_env(void)
{
	extern char **environ;
	//...

	int i = 0;
	while(environ[i]) {
	  printf("%s\n", environ[i++]); // prints in form of "variable=value"
	}
}


int init() 
{
   	unblock_signal(SIGINT);
	unblock_signal(SIGQUIT);
	return(0);
}


//cc main.c  -lreadline 
/*
int init() {
    char *line;
    int salir=0;
    char cwd[1024];

	print_env();
	
//	signal(SIGINT, manejador_sigint);
	block_signal(SIGQUIT);
	block_signal(SIGINT);

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("Directorio actual: %s\n", cwd);
        return 1;
    }

  using_history();    
	while (!salir)	
	{
//	    line = readline(cwd);
		line = readline(READLINE_MSG);
	    if (line[0] == 'x')
	    {
	    	salir = 1;
	    }
	    add_history(line);
		free(line);    
	}
	 
    //printf("La línea ingresada es: %s\n", line);


    
   	unblock_signal(SIGINT);
	unblock_signal(SIGQUIT);
	
    return 0;
}
*/