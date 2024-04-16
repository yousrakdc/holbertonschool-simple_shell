#include "shell.h"


/**
 * builtins_check - Checks if a command is built-in
 * @args: array of arguments
 * Return: Pointer to the corresponding function if the command is built-in
 * otherwise NULL
 */

void(*builtins_check(char **args))(char **args)
{
	int i, j;

	mybuild T[] = {
		{"exit", shell_exit},
		{"env", env},
		{"setenv", set_custom_env},
		{"unsetenv", unset_custom_env},
		{NULL, NULL}
	};

	for (i = 0; T[i].name; i++)
	{
		j = 0;
		if (T[i].name[j] == args[0][j])
		{
			for (j = 0; args[0][j]; j++)
			{
				if (T[i].name[j] != args[0][j])
					break;
			}
			if (!args[0][j])
				return (T[i].func);
		}
	}
	return (0);
}
