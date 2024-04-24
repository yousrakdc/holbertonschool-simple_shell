#include "shell.h"

/**
 * print_env - built-in to prints the environment
 * @environ: environment of the program
 */

void print_env(char **environ)
{
	int i = 0;

	printf("My environment:\n");

	/*Loop through the array of environment variables.*/
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]); /*Print each environment variable.*/
		i++; /*Increment the counter to move to the next variable*/
	}
}
