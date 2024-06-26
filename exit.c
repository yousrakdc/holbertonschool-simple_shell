#include "shell.h"

void free_list(list_path *head);

/**
 * exit_program - built-in to exits the shell
 * @command: Pointer to the command string. Will be freed if not NULL.
 * @head: Pointer to the head of the linked list of paths. Will be freed.
 * @exit_value: the value to return on exit
 */

void exit_program(char *command, list_path *head, int exit_value)
{
	/* Clean up the command string if it is not NULL */
	if (command)
	{
		free(command);
		command = NULL; /* Set command to NULL to prevent dangling pointer issues */
	}

	/* Clean up the linked list if it is not NULL */
	if (head)

		/*Free the linked list of paths using the free_list function*/
		free_list(head);

	/* Exit the program with the specified exit status */
	exit(exit_value);
}
