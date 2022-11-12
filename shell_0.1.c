#include "main.h"
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
	char line[1024];
	int count = 0, i = 0, j = 0;
	char *pch;
	char *array[100];

	/*reads one line*/
	for (;;)
	{
		int c = fgetc(stdin);

		line[count++] = (char)c;
		if (c == '\n')
		{
			return;
		}
	}

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
	par[i] = NULL;  /*null terminating the parameter list*/
}

/**
 * the_prompt - prompts the user to enter a command.
 *
 * Return: always void
 */

void the_prompt(void)
{
	printf("#cisfun$ ");
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
	char *para[20];

	/*creating environment variable*/
	char *envp[] = {(char *)"PATH=/bin", NULL};

	while (1)
	{					   /*repeat forever*/
		the_prompt();			   /*display prompt on screen*/
		read_command(command, para); /*read input from terminal*/
		if (fork() != 0)		   /*parent*/
		{
			wait(NULL); /*wait for child precesses to finish*/
		}
		else
		{
			strcpy(cmd, "/bin/");
			strcat(cmd, command);
			execve(cmd, para, envp); /*execute command*/
		}

		if (strcmp(command, "exit") == 0)
		{
			break;
		}
	}
	return (0);
}
