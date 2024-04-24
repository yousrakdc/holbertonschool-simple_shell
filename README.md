add picture!

# Simple Shell Project

This is our end-of-trimester project, part of our Holberton School formation.
This project was completed using C language Shell Betty linter.

## What's a Shell?

It's a command-line interface program that provides users with a way to interact with the operating system by accepting and executing commands. It acts as an intermediary between the user and the kernel of the operating system, facilitating tasks such as launching programs, managing files, and controlling system resources.

## Files description

List of files

- `man_1_simple_shell`: Manual page for the project
- `AUTHORS`: List of contributors to this repository
- `shell.h`: Header file
- `very_simple_shell.c`:  Main function
- `print_env.c`: Prints the environment
- `exit.c`: Handles the exit command
- `_getenv.c`: Return the value of a global variable
- `path.c`: Creates linked list of PATH

## List of allowed functions and system calls for this project

- all functions from string.h
- access (man 2 access)
- chdir (man 2 chdir)
- close (man 2 close)
- closedir (man 3 closedir)
- execve (man 2 execve)
- exit (man 3 exit)
- _exit (man 2 _exit)
- fflush (man 3 fflush)
- fork (man 2 fork)
- free (man 3 free)
- getcwd (man 3 getcwd)
- getline (man 3 getline)
- getpid (man 2 getpid)
- isatty (man 3 isatty)
- kill (man 2 kill)
- malloc (man 3 malloc)
- open (man 2 open)
- opendir (man 3 opendir)
- perror (man 3 perror)
- printf (man 3 printf)
- fprintf (man 3 fprintf)
- vfprintf (man 3 vfprintf)
- sprintf (man 3 sprintf)
- putchar (man 3 putchar)
- read (man 2 read)
- readdir (man 3 readdir)
- signal (man 2 signal)
- stat (__xstat) (man 2 stat)
- lstat (__lxstat) (man 2 lstat)
- fstat (__fxstat) (man 2 fstat)
- strtok (man 3 strtok)
- wait (man 2 wait)
- waitpid (man 2 waitpid)
- wait3 (man 2 wait3)
- wait4 (man 2 wait4)
- write (man 2 write)

## How to use our code

You can try to use our code by following these simple steps:

> First, you need to clone our repository using this command:
````
git clone https://github.com/yousrakdc/holbertonschool-simple_shell.git
`````

> Then, you need to change your directory:
`````
cd holbertonschool-simple_shell
`````

> Compile the C file:
`````
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
``````

> Run the shell:
``````
./hsh
``````

> To exit, you can type the command "exit"
`````
exit
``````

> or type CTRL + D.

## Example of usage

## Bugs

No known bugs.

## Authors

- [@samjouini](https://www.github.com/samjouini)
- [@yousrakdc](https://www.github.com/yousrakdc)
