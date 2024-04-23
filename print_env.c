#include "shell.h"

/**
 * print_env - built-in to prints the environments
 * @environ: environment of the program
 */

void print_env(char **environ)
{
	int i = 0;

	printf("My environment:\n");
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
