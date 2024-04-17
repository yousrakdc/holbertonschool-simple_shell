#include "shell.h"

/**
 * main - UNIX command line interpreter
 * Return: 0
 */

int main(void)
{
	char *file;

	while (1)
	{
		file = get_filename();
		execute_it(file);
	}
}

/**
 * get_filename - read the filenama given by the user
 * Return: the name of the file to execute
 */

char *get_filename()
{
	char *filename = NULL;
	size_t lenght;
	int input;


	printf("€ ");
	input = getline(&filename, &lenght, stdin);

	if (input == -1)
	{
		printf("ctrl D \n");
		free(filename);
		exit(1);
	}
	filename[input - 1] = '\0';

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
	char *argv[2];
	char *envp[1];
	int argc = 0;
	char *token;

	argv[0] = filename;
	argv[1] = NULL;
	envp[0] = NULL;

	token = strtok(filename, " ");
	while (token != NULL)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}

	pid = fork();

	if (pid == 0)
	{
		printf("execute command : %s \n", filename);
		if (execve(filename, argv, envp) == -1)
		{
			perror("Echec");
			exit(1);
		}
	}
	else if (pid == -1)
	{

		printf("Echec : fork failure");
	}
	else
	{
		printf("i'm waiting \n");
		waitpid(pid, NULL, 0);
	}

	return (0);
}

