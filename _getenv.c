#include "shell.h"

/**
 * _getenv - searches the environment list to find the
 * environment variable name
 * @name: name of the environnement to find
 * Return: pointer to the corresponding string or NULL if not found
*/

char *_getenv(const char *name)
{
	size_t length;
	int i;

	/* Checks if name exists */
	if (name == NULL)
	{
		return (NULL);
	}

	/* Create a copy of the variable */
	length = strlen(name);

	/* Loop through the array of environments to compare them */
	for (i = 0; environ[i] != NULL; i++)
	{
		/* Compare the variable's copy to the list of environment */
		if (strncmp(environ[i], name, length) == 0 && environ[i][length] == '=')
		{
			return (&environ[i][length + 1]);
		}
	}

	return (NULL);
}
