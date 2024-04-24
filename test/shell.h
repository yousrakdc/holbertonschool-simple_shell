#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

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

int main(void);
char *get_filename();
int execute_it(char *);

void(*builtins_check(char **args))(char **args);
void shell_exit(char **args);
void print_env(char **args);

#endif
