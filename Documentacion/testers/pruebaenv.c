#include <stdlib.h>
int main(int ac, char **av, char**env)
{
	ac = 9;
	av[0] = "lol";
	free(env);
	return (0);
}
