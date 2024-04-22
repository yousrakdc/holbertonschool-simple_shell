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

	if (name == NULL)
	{
		return (NULL);
	}

	length = strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, length) == 0 && environ[i][length] == '=')
		{
			return (&environ[i][length + 1]);
		}
	}

	return (NULL);
}
