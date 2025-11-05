#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	char *read;

	add_history("Me encontraste o.o\n");
	read = readline("Dime: ");

	printf("%s tu gilipollas.\n", read);
	rl_clear_history();
	rl_on_new_line();
	read = readline("Dimelo otra vez: ");
	printf("El idiota dice %s\n", read);
	free(read);
	return (0);
}
