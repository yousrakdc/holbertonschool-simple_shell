#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
 * token - Tokenizes a string
 * @str: User input string
 * Return: Pointer to array of tokens
 */
char **token(char *str)
{
	char **tokens;
	char *token;
	unsigned int i;

	tokens = (char **)malloc(BUFFER_SIZE * sizeof(char *));
	if (!tokens)
	{
		fprintf(stderr, "Error: Memory allocation failure in tokenizer.\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(str, "\n\t\r ");
	i = 0;
	while (token != NULL && i < BUFFER_SIZE - 1)
	{
		/* Allocate memory for each token and copy it*/
		tokens[i] = (char *)malloc((strlen(token) + 1) * sizeof(char));
		if (!tokens[i])
		{
			/* Free previously allocated memory*/
			for (unsigned int j = 0; j < i; j++)
				free(tokens[j]);

			free(tokens);
			fprintf(stderr, "Error: Memory allocation failure in tokenizer.\n");
			exit(EXIT_FAILURE);
		}
		strcpy(tokens[i], token);
		i++;

		/* Get the next token*/
		token = strtok(NULL, "\n\t\r ");
	}

	tokens[i] = NULL;

	return (tokens);
}

