#include "shell.h"

/**
 * _path - Creates a linked list for path directories
 * @path: string of path value
 * Return: pointer to the created linked list, or NULL on failure
 */
list_path *_path(const char *path)
{
	char *cpath, *token;
	list_path *head;

	if (!path)
		return (NULL); /* Handle NULL input gracefully */

	cpath = strdup(path); /* Use strdup to copy path */
	if (!cpath)
		return (NULL); /* Memory allocation failure */

	head = NULL;
	token = strtok(cpath, ":");

	while (token)
	{
		if (!add_node_end(&head, token))
		{
			free_list(head); /* Free list and cpath on error */
			free(cpath);
			/* maybe free the token here too*/
			return (NULL);
		}
		token = strtok(NULL, ":");
	}
	free(cpath);
	return (head);
}

/**
 * add_node_end - Adds a new node to the end of a linked list
 * of path directories.
 * @head: Pointer to the head of the linked list.
 * @path: Path string to be added to the list.
 * Return: Pointer to the newly added node, or NULL on failure.
 */

list_path *add_node_end(list_path **head, const char *path)
{
	/* Allocate memory for the new node */
	list_path *new_node = (list_path *)malloc(sizeof(list_path));

	if (!new_node)
		return (NULL);

	/* Allocate memory for the path string in the new node */
	new_node->path = (char *)malloc(strlen(path) + 1);
	if (!new_node->path)
	{
		free(new_node);
		return (NULL);
	}

	/* Copy the path string to the new node */
	strcpy(new_node->path, path);

	new_node->next = NULL;

	/* Check if the linked list is empty */
	if (*head == NULL)
		*head = new_node;
	else
	{
		/* Traverse the list to find the end */
		list_path *current = *head;

		while (current->next != NULL)
			current = current->next;

		current->next = new_node;
	}

	return (new_node);
}

/**
 * which_path - finds the pathname of a filename
 * @command: string representing a command name
 * @head: head of linked list of path directories
 * Return: pathname of filename or NULL if no match or on error
 */
char *which_path(char *command, list_path *head)
{
	struct stat st;
	char *string = NULL;
	size_t required_length;

	list_path *tmp = head;

	if (command == NULL)
		return (NULL);

	while (tmp) /* Loop through each directory in the list */
	{
		/* Allocate memory for the concatenated path*/
		required_length = strlen(tmp->path) + strlen("/") + strlen(command) + 1;
		string = (char *)malloc(required_length);

		if (string == NULL)
			return (NULL);

		/* Construct the full path*/
		strcpy(string, tmp->path);
		strcat(string, "/");
		strcat(string, command);

		/* Check if the file exists at this path*/
		if (stat(string, &st) == 0)
		{
			return (string);
		}

		free(string);
		string = NULL;

		tmp = tmp->next;
	}

	fprintf(stderr, "Error: Command not found: %s\n", command);
	return (NULL);
}

/**
 * free_list - Frees a linked list of path directories.
 * @head: Pointer to the head of the linked list.
 */
void free_list(list_path *head)
{
	list_path *next_node;

	while (head) /* Traverse the list and free each node */
	{
		next_node = head->next;
		free(head->path);
		free(head);
		head = next_node;
	}
}
