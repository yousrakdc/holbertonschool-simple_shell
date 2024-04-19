#include "shell.h"

/**
 * path - Creates a linked list for path directories
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
			/* Free list and cpath on error */
			free_list(head);
			free(cpath);
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
		return (NULL); /* Memory allocation failure */

	/* Allocate memory for the path string in the new node */
	new_node->path = (char *)malloc(strlen(path) + 1);
	if (!new_node->path)
	{
		free(new_node);
		return (NULL); /* Memory allocation failure */
	}

	/* Copy the path string to the new node */
	strcpy(new_node->path, path);

	/* Initialize the next pointer to NULL */
	new_node->next = NULL;

	/* Check if the linked list is empty */
	if (*head == NULL)
	{
		*head = new_node; /* Set the new node as the head of the list */
	}
	else
	{
		/* Traverse the list to find the end */
		list_path *current = *head;

		while (current->next != NULL)
			current = current->next;

		/* Add the new node at the end of the list */
		current->next = new_node;
	}

	/* Return the newly added node */
	return (new_node);
}

/**
 * which_path - finds the pathname of a filename
 * @filename: name of file or command
 * @head: head of linked list of path directories
 * Return: pathname of filename or NULL if no match or on error
 */
char *which_path(char *filename, list_path *head)
{
	struct stat st;
	char *string = NULL;
	size_t required_length;

	list_path *tmp = head;

	if (filename == NULL)  /* Check if filename is NULL*/
		return (NULL);

	while (tmp) /* Loop through each directory in the list */
	{
		/* Allocate memory for the concatenated path*/
		required_length = strlen(tmp->path) + strlen("/") + strlen(filename) + 1;
		string = (char *)malloc(required_length);
		strcpy(string, tmp->path);

		if (string == NULL)
			return (NULL); /* Memory allocation error*/

		/* Construct the full path*/
		strcpy(string, tmp->path);
		strcat(string, "/");
		strcat(string, filename);

		/* Check if the file exists at this path*/
		if (stat(string, &st) == 0)
			return (string); /* File found*/

		/* Free the memory allocated for the path*/
		free(string);
		string = NULL;

		tmp = tmp->next; /* Move to the next directory*/
	}

	return (NULL); /* File not found*/
}

/**
 * free_list - Frees a linked list of path directories.
 * @head: Pointer to the head of the linked list.
 */
void free_list(list_path *head)
{
	/* Variable to hold the next node while traversing the list */
	list_path *next_node;

	while (head) /* Traverse the list and free each node */
	{
		next_node = head->next; /* Store the next node */
		free(head->path); /* Free the path string */
		free(head); /* Free the current node */
		head = next_node; /* Move to the next node */
	}
}
