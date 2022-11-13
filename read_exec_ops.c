#include "main.h"

/**
 * _exec - this function executes commands
 * Description: executes commands entered by he user
 * @args: commands entered by user
 * Return: void
 */
void _exec(char **args)
{
	for (int i = 0; i < _num_builtins(); i++)
	{
		if (strcmp(args[0], builtins[i].name) == 0)
		{
			builtins[i].func(args);
			return;
		}
	}

	pid_t child_pid = fork();

	if (child_pid == 0)
	{
		execvp(args[0], args);
		perror("");
		exit(1);
	}
	else if (child_pid > 0)
	{
		int status;

		do {
			waitpid(child_pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	else
	{
		perror("kash");
	}
}

/**
 * _split_line - this function executes commands
 * Description: this function splits the string into tokens
 * @line: string entered into the shell by the user
 * Return: void
 */

char **_split_line(char *line)
{
	int length = 0;
	int capacity = 16;

	char **tokens = malloc(capacity * sizeof(char *));

	if (!tokens)
	{
		perror("kash");
		exit(1);
	}

	char *delimiters = " \t\r\n";
	char *token = strtok(line, delimiters);

	while (token != NULL)
	{
		tokens[length] = token;
		length++;

		if (length >= capacity)
		{
			capacity = (int)(capacity * 1.5);
			tokens = realloc(tokens, capacity * sizeof(char *));
			if (!tokens)
			{
				perror("kash");
				exit(1);
			}
		}

		token = strtok(NULL, delimiters);
	}

	tokens[length] = NULL;
	return (tokens);
}

/**
 * _read_line - Reads a line
 * Description: reads a single line of input from stdin
 * Return: The return value is a string pointer which needs
 * to be freed once we're finished with it.
 */

char *_read_line()
{
	char *line = NULL;
	size_t buflen = 0;
	ssize_t strlen = getline(&line, &buflen, stdin);

	errno = 0;

	if (strlen < 0)
	{
		if (errno)
		{
			perror("kash");
		}
		exit(1);
	}
	return (line);
}
