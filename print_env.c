#include "shell.h"

/**
 * print_env - built-in to prints the environment
 * @args: array of arguments
 */

char *print_env(const char *name)
{
	const char *value = _getenv(name);
	char *copy;

	/* Check if the environment variable exists */
	if (value != NULL)
	{
		/* Make a copy of the string */
		copy = malloc(strlen(value) + 1);
		if (copy != NULL)
		{
			strcpy(copy, value);
			/* Print the name and value of the environment variable */
			return (copy);
		}
		else
		{
			/* Handle memory allocation failure */
			printf("Error: Unable to allocate memory\n");
			return (NULL);
		}
	}
	else
	{
		/* If the environment variable is not found, print a message */
		printf("%s = not found\n", name);
		return (NULL);
	}
}
