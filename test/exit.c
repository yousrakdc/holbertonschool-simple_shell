#include "shell.h"

/**
 * shell_exit - built-in to exits the shell with or without a return status n
 * @args: Array of words of the entered line
 */

void shell_exit(char **args)
{
	int i;
	int status = 0;

	if (args[1] != NULL)
	{
		status = atoi(args[1]); /* Convert the argument to an integer*/
		if (status < 0)
			status = 2; /* Default exit status if the argument is negative */
	}

	for (i = 0; args[i] != NULL; i++) /* Free memory */
		free(args[i]);

	free(args);
	exit(status);
}
