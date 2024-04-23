#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Externe variable */

extern char **environ;

void _puts(char *str);
int _strlen(char *s);

void _isatty(void);
int main(void);
char *get_command();
char *get_filename();
int execute_it(char *);

/* path */

/**
 * struct list_path - inked list of path directories
 * @path: path directory
 * @next: pointer to next node
 */

typedef struct list_path
{
	char *path;
	struct list_path *next;
} list_path;

list_path *_path(const char *path);
list_path *add_node_end(list_path **head, const char *path);
char *which_path(char *filename, list_path *head);
void free_list(list_path *head);

/* prototypes for builtins*/

void print_env(char **environ);
void exit_program(char *command, list_path *head, char *resolved_path);

/* implementation of getenv*/

char *_getenv(const char *name);

/* token */

char **token(char *str);

#endif
