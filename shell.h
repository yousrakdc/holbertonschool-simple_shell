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

/* Extern variable */

extern char **environ;

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

void _puts(char *str);
int _strlen(char *s);

/* main */

int main(void);
char *get_command();
char **parse_command(char *command);
int execute_it(char *command, list_path *head);
/* path */

list_path *_path(const char *path);
list_path *add_node_end(list_path **head, const char *path);
char *which_path(char *filename, list_path *head);
void free_list(list_path *head);

/* implementation of getenv*/

char *_getenv(const char *name);

/* prototype for print_env*/

void print_env(char **environ);

/* prototype for exit */

void exit_program(char *command, list_path *head);

/* token */

char **token(char *str);

#endif
