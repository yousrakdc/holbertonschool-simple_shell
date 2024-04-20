#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(void);
char *get_command();
int execute_it(char *);

/* prototype for print_env*/

char *print_env(const char *name);

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

#endif
