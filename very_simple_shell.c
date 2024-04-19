#include "shell.h"

#define MAX_ARGS 20

/**
 * main - UNIX command line interpreter
 * Return: 0
 */

int main(void)
{
	char *file;
	list_path *head = NULL;
	char *value = NULL;

	value = print_env("PATH");

	if (value)
	{
		head = _path(value);
	}
	free (value);

	while (1)
	{
		file = get_filename();
		if (!file)
			break;

		file = which_path(file, head);

		if (file)
		{
			execute_it(file);
			free(file);
		}
		else
			execute_it(file);
	}
	free(file);

	if (head)
		free_list(head);
	return (0);
}

/**
 * get_filename - read the filename given by the user
 * Return: the name of the file to execute
 */

char *get_filename()
{
	char *filename = NULL;
	size_t length;
	int input;


	printf("~B ");
	input = getline(&filename, &length, stdin);

	if (input == -1)
	{
		printf("ctrl D \n");
		free(filename);
		exit(EXIT_FAILURE); /* Better error handling */
	}

	return (filename);

}


/**
 * execute_it - execute a command in a child process
 * @filename: the filename to execute
 * Return: 0 on success or -1 on failure
 */

int execute_it(char *filename)
{
	pid_t pid;
	char *argv[MAX_ARGS + 1]; /* One extra for NULL */
	int argc = 0;
	char *token;

	token = strtok(filename, " ");

	while (token != NULL && argc < MAX_ARGS)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}

	argv[argc] = NULL;

	pid = fork();

	if (pid == 0)
	{
		printf("execute command : %s \n", filename);
		if (execv(argv[0], argv) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid == -1)
	{
		printf("Error : fork failure");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("I'm waiting \n");
		waitpid(pid, NULL, 0);
	}

	return (0);
}
