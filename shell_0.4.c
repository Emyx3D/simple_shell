#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * read_command - reads commands entered by the user into the shell.
 *
 * @cmd: holds the command itself
 * @par: holds the parameters that can be used
 *
 * Return: always void
 */

void read_command(char cmd[], char *par[])
{
        char *line;
        size_t buflen = 64;
        int chars;
        int count = 0, i = 0, j = 0;
        char *pch;
        char *array[100];

        /*reads one line*/
        line = (char *)malloc(buflen * sizeof(char));
        if (line == NULL)
        {
                perror("unable to allocate memory...");
                exit(1);
        }
        chars = getline(&line, &buflen, stdin);
        line[count++] = (char)chars;

        if (count == 1)
        {
                return;
        }

        /*parse the line into words*/
        pch = strtok(line, " \n");
        while (pch != NULL)
        {
                array[i++] = strdup(pch);
                pch = strtok(NULL, " \n");
        }

        /*first word is the command*/
        strcpy(cmd, array[0]);

        /*others are parameters*/
        for (j = 0; j < i; j++)
        {
                par[j] = array[j];
        }
        par[i] = NULL;
}

/**
 * the_prompt - prompts the user to enter a command.
 *
 * Return: always void
 */

void the_prompt(void)
{
        int first_time = 1;

        while (first_time) /*prompts an infinite loop for the user to enter commands*/
        {
                write(STDOUT_FILENO, "#cisfun$ ", 10);
                first_time = 0;
        }
}

/**
 * main - shell main file
 * @argc: holds argument counts
 * @argv: holds argument lists
 * Return: always 0
 */
int main(int argc, char *argv[])
{
        char cmd[1000];
        char command[1000];
        char *parameters[20];

        /*creating environment variable*/
        char *envp[] = {(char *)"PATH=/usr/bin/", NULL};

        while (1)
        {                                          /*repeat forever*/
                the_prompt();                      /*display prompt on screen*/
                read_command(command, parameters); /*read input from terminal*/
                if (fork() != 0)                   /*parent*/
                {
                        wait(NULL); /*wait for child precesses to finish*/
                }
                else
                {
                        strcpy(cmd, "/usr/bin/");
                        strcat(cmd, command);
                        execve(cmd, parameters, envp); /*execute command*/
                }

                if (strcmp(cmd, "exit") == 0)
                {
                        break;
                }
        }
        return (0);
}
