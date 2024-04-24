#include "shell.h"
#include <string.h>

#define MAX_ARGS 20

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
