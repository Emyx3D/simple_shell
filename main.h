#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

struct builtin
{
    char *name;
    void (*func)(char **args);
};

struct builtin builtins[] = {
    {"help", _help},
    {"exit", _exit},
    {"cd", _cd},
};

void _exit(char **args);
int _num_builtins();
void _help(char **args);
void _cd(char **args);
void _exit(char **args);
void _exec(char **args);
char **_split_line(char *line);
char *_read_line();

#endif
