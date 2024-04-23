#include "shell.h"

/**
 * print_env - built-in to prints the environment
 * @args: array of arguments
 */

 void print_env(void)
{
	int i = 0;

	while(environ[i] != NULL)
	{
		printf("Environ: %s", environ);
		i++;
	}
}
