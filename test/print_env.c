#include "shell.h"

/**
 * print_env - built-in to prints the environment
 * @args: array of arguments
 */

void print_env(char **args)
{
	int i;
	char **env = NULL;
	(void)args;

	for (i = 0; env[i]; i++)
	{
		printf("%s", env[i]);
	}
}
