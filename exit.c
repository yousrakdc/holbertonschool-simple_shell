#include "shell.h"

void free_list(list_path *head);

/**
 * exit_program - built-in to exits the shell
 * @command: Pointer to the command string. Will be freed if not NULL.
 * @head: Pointer to the head of the linked list of paths. Will be freed.
 */

void exit_program(char *command, list_path *head)
{
	/* If the command string is not NULL */
	if (command)
	{
		free(command);
		command = NULL; /* Set the command pointer to NULL for safety*/
	}

	/* If the head of the path list is not NULL*/
	if (head)
	{
		/*Free the linked list of paths using the free_list function*/
		free_list(head);
	}

	/* Exit the program with status code 0 (success)*/
	exit(0);
}
