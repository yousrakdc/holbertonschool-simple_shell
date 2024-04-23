#include "shell.h"

/**
 * exit_program - built-in to exits the shell
 * @command: Pointer to the command string. Will be freed if not NULL.
 * @head: Pointer to the head of the linked list of paths. Will be freed.
 */

void exit_program(char *command, list_path *head)
{
	if (command)
	{
		free(command);
		command = NULL;
	}

	if (head)
	{
		free_list(head);
	}

	exit(0);
}
