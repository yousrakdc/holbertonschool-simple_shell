#include "shell.h"

/**
 * exit_program - built-in to exits the shell
 * @command: Pointer to the command string. Will be freed if not NULL.
 * @resolved_path: Pointer to the resolved path string. Freed if not NULL.
 * @head: Pointer to the head of the linked list of paths. Will be freed.
 */

void exit_program(char **args)
{
	char *command;
	list_path *head;
	char *resolved_path;

	if (command)
	{
		free(command);
		command = NULL;
	}

	if (resolved_path)
	{
		free(resolved_path);
		resolved_path = NULL;
	}

	if (head)
	{
		free_list(head);
	}

	exit(0);
}
