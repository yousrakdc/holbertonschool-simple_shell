#include "shell.h"
#include <string.h>

#define MAX_ARGS 20

/**
 * get_command - reads the command given by user
 * Return: the command entered by the user
 */

char *get_command()
{
	char *command = NULL;
	size_t length = 0;
	int input;

	printf("$ ");
	input = getline(&command, &length, stdin);

	if (input == -1)
	{
		printf("ctrl D \n");
		free(command);
		exit(1);
	}
	if (command[input - 1] == '\n')
		command[input - 1] = '\0';

	return (command);
}

/**
 * execute_command - execute a command with its arguments in a child process
 * @command: command to execute
 */

void execute_command(char *command)
{
	char *token;
	char *argv[MAX_ARGS]; /*Maximum number of arguments */
	int argc = 0;
	pid_t pid;

	token = strtok(command, " ");
	while (token != NULL)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}

	argv[argc] = NULL;

	/* execute the command */
	pid = fork();

	if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
		{
			perror("Execution error");
			exit(EXIT_FAILURE);
		}
	}

	else if (pid > 0)
		/* parent process */
		wait(NULL); /* wait for the child process to finish*/

	else
	{
		/* fork failed */
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
}
