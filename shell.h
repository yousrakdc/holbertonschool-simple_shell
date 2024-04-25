#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Externe variable */
extern char **environ;

/* Path handling */

/**
 * Struct list_path - linked list of path directories
 * @path: path directory
 * @next: pointer to next node
 */

typedef struct list_path
{
	char *path;
	struct list_path *next;
} list_path;

/* Main */
int main(void);
char *get_command();
char **parse_command(char *command);
int execute_it(char *command, list_path *head);

/* Parsing */
list_path *_path(const char *path);
list_path *add_node_end(list_path **head, const char *path);
char *which_path(char *filename, list_path *head);
void free_list(list_path *head);

/* Implementation of getenv */
char *_getenv(const char *name);

/* Buildins-in prototypes */
/* Prototype for print_env*/
void print_env(char **environ);

/* Prototype for exit */
void exit_program(char *command, list_path *head, int exit_value);

#endif
