#include "shell.h"

/**
 * shell_exit - Exits the shell with or without a return status n
 * @args: Array of words of the entered line
*/

void shell_exit(char **args)
{
    int i;
    int status = 0;

    if (args[1] != NULL)
    {
        status = _atoi(args[1]); /* Convert the argument to an integer*/
        if (status < 0)
            status = 2; /* Default exit status if the argument is negative */
    }

    for (i = 0; args[i] != NULL; i++) /* Free memory */
        free(args[i]);
    
    free(args);
    exit(status); 
}

/**
 * _atoi - Converts a string into an integer.
 * @s: Pointer to a string.
 * Return: The integer.
 */
int _atoi(char *s) 
{
    int integer = 0;
    int sign = 1;

    while (*s != '\0' && (*s < '0' || *s > '9')) 
    {
        if (*s == '-') 
            sign *= -1;
        s++;
    }

    /* Convert digits to integer */
    while (*s >= '0' && *s <= '9') 
    {
        integer = integer * 10 + (*s - '0');
        s++;
    }

    return (integer * sign);
}


/**
 * env - prints the environment
 * @args: array of arguments
 */

void env(char **args __attribute__ ((unused)))
{       
        int i;
        char **environ;
        
        for (i = 0; environ[i]; i++);
        {
                _puts(environ[i]);
                _puts("\n");
        }       
}       

/**
 * set_custom_env - new environment variable, or modifies
 * @args: array of strings
 */

void set_custom_env(char **args)
{
    int i, j, k;
    char **environ;

    if (!args[1] || !args[2])
    {
        perror("setenv"); /*print an error message if not enought args*/
        return;
    }

    for (i = 0; environ[i]; i++)
    {
        if (strncmp(args[1], environ[i], strlen(args[1])) == 0 && environ[i][strlen(args[1])] == '=') 
        /*Update the value of the environment variable*/
        {
            if (setenv(args[1], args[2], 1) != 0)
                perror("setenv"); /*Print an error message if setenv fails*/
            return;
        }
        
    }

    if (setenv(args[1], args[2], 1) != 0) /* Add environment variable if it doesn't exist*/
        perror("_setenv"); /* pritn error message if failure*/
}

/**
 * unset_custom_env - Remove an environment variable
 * @args: array of entered words
*/

int unset_custom_env(char **args)
{
    if (!args[1])
    {
        perror("unsetenv"); /* Print an error message if insufficient arguments provided*/
        return;
    }

    /*Use unsetenv to remove the environment variable*/

    if (unsetenv(args[1] != 0))
        perror("_unsetenv"); /* Print an error message if unsetenv fails*/

}
