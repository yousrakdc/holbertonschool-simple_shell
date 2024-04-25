#include "shell.h"

#define MAX_ARGS 20

/**
 * main - UNIX command line interpreter
 * Return: 0
 */

int main(void)
{
	char *command;
	list_path *head = NULL;
	char *value = NULL;

		value = _getenv("PATH");

	/* If the PATH variable is found, create a linked list of paths. */
		if (value)
		{
			head = _path(value);
		}

		while (1)
		{
			command = get_command();
			if (!command)
				break; /*if ctrl + D = NULL -> exit the loop*/

			else if (strcmp(command, "exit") == 0)
				exit_program(command, head);

			else if (strcmp(command, "env") == 0)
			{
				print_env(environ);
				free(command);
			}

			else
			{
				execute_it(command, head);
				free(command);
			}
		}

	free_list(head);
	return (0);
}

/**
 * get_command - read the command given by the user
 * Return: the name of the file to execute
 */

char *get_command()
{
	char *command = NULL;
	size_t length = 0;
	int input;

	if (isatty(STDIN_FILENO))
	{
		printf("~€ ");
	}

	input = getline(&command, &length, stdin);

	if (input == -1)
	{
		free(command);
		return (NULL); /* You need me to patch the leak*/
	}

	if (command[input - 1] == '\n')
		command[input - 1] = '\0';

	return (command);
}

/**
 * parse_command - define if command is a path or not
 * @command: the command to execute
 * Return: Argv aka the command to execute
*/

char **parse_command(char *command)
{
	int argc = 0;
	char *token;
	char **argv;

	argv = malloc(sizeof(char *) * MAX_ARGS + 1);
	token = strtok(command, " ");

	while (token != NULL && argc < MAX_ARGS)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}

	argv[argc] = NULL;

	return (argv);
}

/**
 * execute_it - execute a command in a child process
 * @command: the command to execute
 * @head: the linked list used to parse
 * Return: 0 on success or -1 on failure
 */

int execute_it(char *command, list_path *head)
{
	pid_t pid;
	char **argv;
	int freeArg0 = 0;

	argv = parse_command(command);

	if (argv[0][0] != '/' && argv[0][0] != '.')
	{
		argv[0] = which_path(argv[0], head);
		freeArg0 = 1;
	}
	
	pid = fork();

	if (pid == 0)
	{
		if (execv(argv[0], argv) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid == -1)
	{
		printf("Error : fork failure");
		if (freeArg0 == 1)
			free(argv[0]);
		free(argv);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (freeArg0 == 1)
			free(argv[0]);
		free(argv);
		waitpid(pid, NULL, 0);
	}

	return (0);
}
