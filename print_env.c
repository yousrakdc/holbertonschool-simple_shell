#include "shell.h"

/**
 * print_env - built-in to prints the environments
 */

void print_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("My environment: %s", environ[i]);
		i++;
	}
}
