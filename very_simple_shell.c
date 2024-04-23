#include "shell.h"
#include <signal.h>

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
		head = _path(value);

	while (1) /* Main loop to read and execute commands. */
	{
		command = get_command();
		if (!command)
			break; /*if ctrl + D = NULL -> exit the loop*/

		/* Handle specific commands such as "exit" and "env"*/
		if (strcmp(command, "exit") == 0)
		{
			exit_program(command, head);
			free(command);
			free_list(head);
			return (0);
		}

		else if (strcmp(command, "env") == 0)
		{
			print_env(environ);
			free(command);
		}
		else
		{
			/* Execute other commands using the execute_it function.*/
			execute_it(command, head);
			free(command);
		}
	}
	free_list(head); /* Free the linked list of paths when program finishes.*/
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

	/* Check if the standard input is a terminal (interactive mode).*/
	if (isatty(STDIN_FILENO) != 0)
		printf("~€ ");

	input = getline(&command, &length, stdin);

	if (input == -1)
	{
		free(command);
		return (NULL); /* indicates no input */
	}

	/* Check if the last character in the command is a newline.*/
	if (command[input - 1] == '\n')
		/*Replace the newline character with a null terminator.*/
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

	/* Allocate memory for the array of arguments */
	argv = malloc(sizeof(char *) * MAX_ARGS + 1);
	if (argv == NULL)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}
	argc = 0;
	token = strtok(command, " ");

	/* Loop to parse each token and store it in the argv array. */
	while (token != NULL && argc < MAX_ARGS)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}

	argv[argc] = NULL; /* Ensure the argument list is NULL-terminated. */

	return (argv); /* Return the array of parsed arguments. */
}

/**
 * execute_it - execute a command in a child process
 * @command: the command to execute
 * Return: 0 on success or -1 on failure
 */

int execute_it(char *command, list_path *head)
{
	pid_t pid;
	char **argv;
	int freeArg0 = 0;
	char *resolved_path;

	argv = parse_command(command); /* Parse the command string to get the array of args. */

	if (!argv)
	{
		perror("Allocation error");
		return (-1);
	}

	if (!argv[0])
	{
		perror("Invalid command");
		free_argv(argv, freeArg0);
		return (-1);
	}

	if (argv[0][0] != '/' && argv[0][0] != '.')
	{
		resolved_path = which_path(argv[0], head);
		if (!resolved_path)
		{
			perror("Command not found");
			free(argv);
			return (-1);
		}
		argv[0] = resolved_path;
		freeArg0 = 1;
	}
	pid = fork();

	if (pid == 0) /*Check if the fork operation was successful.*/
	{
		execv(argv[0], argv);/* Try to execute the command using execv.*/
		perror("Error");
		free_argv(argv, freeArg0);
		exit(EXIT_FAILURE);

	}
	else if (pid == -1) /* Fork failure */
	{
		perror("Error : fork failure");
		free_argv(argv, freeArg0);
		return (-1);
	}
	else
	{
		waitpid(pid, NULL, 0); /* Wait for the child process to finish.*/
		free_argv(argv, freeArg0);
		return (0);
	}
}

void free_argv(char **argv, int freeArg0)
{
	if (argv[0] && freeArg0 == 1)
		free(argv[0]);
	free(argv);
}
