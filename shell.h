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

void _puts(char *str);
int _strlen(char *s);
char *_strdup(char *str);
char *concat_all(char *name, char *sep, char *value);

void _isatty(void);
int main(void);
char *get_command();
char *get_filename();
int execute_it(char *);

/* prototype for print_env*/

char *print_env(const char *name);

/* prototype for check_builtins*/

typedef void (*build_func)(char **args);

/**
 * struct mybuild - pointer to function
 * @name: buildin command
 * @func: execute the buildin command
 */

typedef struct mybuild
{
	char *name;
	build_func func;
} mybuild;

/* prototypes for builtins*/

void shell_exit(char **args);
void env(char **args __attribute__ ((unused)));
int custom_atoi(char *s); 
void set_custom_env(char **args);
void unset_custom_env(char **args);

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

/* token */

char **token(char *str);
#endif
