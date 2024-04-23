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
	char *resolved_path = NULL;

	if (isatty(STDIN_FILENO))
	{
		value = _getenv("PATH");

		if (value)
		{
			head = _path(value);
		}

		while (1)
		{
			command = get_command();
			if (!command)
				break; /*if ctrl + D = NULL -> exit the loop*/

			if(strcmp(command, "exit") == 0)
				exit_program();

			if(strcmp(command, "env") == 0)
				print_env(environ);

			if (command[0] == '/' || command[0] == '.')
			{
				resolved_path = command;
			}
			else
			{
				resolved_path = which_path(command, head);
				free(command);
			}

			if (resolved_path)
			{
				execute_it(resolved_path);
				free(resolved_path);
			}
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

	printf("~€ ");

	input = getline(&command, &length, stdin);

	if (input == -1)
	{
		printf("ctrl D \n");
		free(command);
		return (NULL); /* You need me to patch the leak*/
	}

	if (command[input - 1] == '\n')
		command[input - 1] = '\0';

	return (command);
}


/**
 * execute_it - execute a command in a child process
 * @command: the command to execute
 * Return: 0 on success or -1 on failure
 */

int execute_it(char *command)
{
	pid_t pid;
	char *argv[MAX_ARGS + 1]; /* One extra for NULL */
	int argc = 0;
	char *token;

	token = strtok(command, " ");

	while (token != NULL && argc < MAX_ARGS)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}

	argv[argc] = NULL;

	pid = fork();

	if (pid == 0)
	{
		printf("execute command : %s \n", command);
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
