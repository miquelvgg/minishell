#include "colors.h"

void	print_msg(char *msg, int exit)
{
	if (exit == EXIT_SUCCESS)
		printf("%s%s%s\n", GREEN, msg, RESET);
	else if (exit == EXIT_FAILURE)
		printf("%s%s%s\n", RED, msg, RESET);
	else
		printf("%s\n", msg);
}
