#include <stdio.h>

int	main(int ac, char **argv, char **env)
{
	int	i;
	i = 0;
	while (i < ac)
	{
		printf("%i:		%s\n", i, argv[i]);
		i++;
	}
	i = 0;/*
	while (env[i])
	{
		printf("env[%i]:	%s", i, env[i]);
		i++;
	}*/
}
