#include "shell.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * shell_exit - Exits the shell with or without a return status n
 * @args: Array of words of the entered line
 */

void shell_exit(char **args)
{
	int i;
	int status = 0;

	if (args[1] != NULL)
	{
		status = custom_atoi(args[1]); /* Convert the argument to an integer*/
		if (status < 0)
			status = 2; /* Default exit status if the argument is negative */
	}

	for (i = 0; args[i] != NULL; i++) /* Free memory */
		free(args[i]);

	free(args);
	exit(status);
}

/**
 * custom_atoi - Converts a string into an integer.
 * @s: Pointer to a string.
 * Return: The integer.
 */
int custom_atoi(char *s)
{
	int integer = 0;
	int sign = 1;

	while (*s != '\0' && (*s < '0' || *s > '9'))
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	/* Convert digits to integer */
	while (*s >= '0' && *s <= '9')
	{
		integer = integer * 10 + (*s - '0');
		s++;
	}
	return (integer * sign);
}

/**
 * env - prints the environment
 * @args: array of arguments
 */

void env(char **args __attribute__ ((unused)))
{
	int i;
	char **environ = NULL;

	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_puts("\n");
	}
}

/**
 * set_custom_env - new environment variable, or modifies
 * @args: array of strings
 */

void set_custom_env(char **args)
{
	int i;
	char **environ = NULL;

	if (!args[1] || !args[2])
	{
		fprintf(stderr, "Usage: set_custom_env VARIABLE VALUE\n");
		/*print an error message if not enought args*/
		return;
	}

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(args[1], environ[i], strlen(args[1])) == 0 &&
				environ[i][strlen(args[1])] == '=')
			/*Update the value of the environment variable*/
		{
			if (setenv(args[1], args[2], 1) != 0)
				fprintf(stderr, "Error updating environment variable %s\n", args[1]);
			/*Print an error message if setenv fails*/
			return;
		}
	}
	if (setenv(args[1], args[2], 1) != 0)
		/* Add environment variable if it doesn't exist*/
		fprintf(stderr, "Error setting environment variable %s\n", args[1]);
	/* pritn error message if failure*/
}

/**
 * unset_custom_env - Remove an environment variable
 * @args: array of entered words
 */

void unset_custom_env(char **args)
{
	if (!args[1])
	{
		fprintf(stderr, "Usage: unset_custom_env VARIABLE\n");
		/* Print an error message if insufficient arguments provided*/
	}

	/*Use unsetenv to remove the environment variable*/

	if (unsetenv(args[1]) != 0)
		fprintf(stderr, "Error unsetting environment variable %s\n", args[1]);
	/* Print an error message if unsetenv fails*/
}
