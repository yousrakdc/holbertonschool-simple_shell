#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void _puts(char *str);
int _strlen(char *s);
char *_strdup(char *str);
char *concat_all(char *name, char *sep, char *value);

int main(void);
char *get_filename();
int execute_it(char *);

/* prototype for commands*/

char *get_command();
void execute_command(char *command);

/* prototype for check_builtins*/

/**
 * struct mybuild - pointer to function
 * @name: buildin command
 * @func: execute the buildin command
 */

typedef void (*build_func)(char **args);

typedef struct mybuild
{
	char *name;
	build_func func;
} mybuild;

void(*builtins_check(char **args))(char **args);

/* prototypes for builtins*/

void shell_exit(char **args);
int custom_atoi(char *s);
void env(char **args __attribute__ ((unused)));
void set_custom_env(char **args);
void unset_custom_env(char **args);

#endif
