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
		return (NULL);

	cpath = strdup(path);
	if (!cpath)
		return (NULL);

	head = NULL;
	token = strtok(cpath, ":");

	while (token)
	{
		if (!add_node_end(&head, token))
		{
			free_list(head);
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
	list_path *new_node = (list_path *)malloc(sizeof(list_path));

	if (!new_node)
		return (NULL);


	new_node->path = (char *)malloc(strlen(path) + 1);
	if (!new_node->path)
	{
		free(new_node);
		return (NULL);
	}

	strcpy(new_node->path, path);

	new_node->next = NULL;

	if (*head == NULL)
		*head = new_node;
	else
	{
		list_path *current = *head;

		while (current->next != NULL)
			current = current->next;

		current->next = new_node;
	}

	return (new_node);
}

/**
 * which_path - finds the pathname of a filename
 * @filename: name of file or command
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

	while (tmp)
	{
		required_length = strlen(tmp->path) + strlen("/") + strlen(command) + 1;
		string = (char *)malloc(required_length);

		if (string == NULL)
			return (NULL);

		strcpy(string, tmp->path);
		strcat(string, "/");
		strcat(string, command);

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

	while (head)
	{
		next_node = head->next;
		free(head->path);
		free(head);
		head = next_node;
	}
}	
