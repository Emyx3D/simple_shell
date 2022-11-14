#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void prog_exit(char **args);
int prog_num_builtins(void);
void prog_help(char **args);
void prog_cd(char **args);
void prog_exec(char **args);
char **prog_split_line(char *line);
char *prog_read_line();

// typedef struct builtin
// {
//     char *name;
//     void (*func)(char **args);
// } inherent;

// inherent progs[] = {
//     {"help", prog_help},
//     {"exit", prog_exit},
//     {"cd", prog_cd},
// };

#endif
