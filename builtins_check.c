#include "shell.h"

/**
 * builtins_check - Checks if a command is built-in
 * @args: array of arguments
 * Return: Pointer to the corresponding function if the command is built-in
 * otherwise NULL
 */

void(*builtins_check(char **args))
{
	int i, j;

	mybuild T[] = {
		{"exit", shell_exit},
		{"env", env},
		{"setenv", set_custom_env},
		{"unsetenv", unset_custom_env},
		{NULL, NULL}
	};

	for (i = 0; T[i].name != NULL; i++)
	{
		j = 0;
		while (T[i].name[j] != '\0' && T[i].name[j] == args[0][j]) 
			j++;

		if (T[i].name[j] == '\0')
			return (T[i].func);
	}
	return (NULL);
}
