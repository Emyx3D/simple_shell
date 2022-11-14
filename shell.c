#include "main.h"

typedef struct builtin
{
	char *name;
	void (*func)(char **args);
} inherent;

inherent progs[] = {
    {"help", prog_help},
    {"exit", prog_exit},
    {"cd", prog_cd},
};

/**
 * prog_num_builtins - number of builtin functions
 * Description: checks the number of builtin commands
 * Return: integer value
 */
int prog_num_builtins(void)
{
	return (sizeof(progs) / sizeof(struct builtin));
}

/**
 * prog_exec - this function executes commands
 * Description: executes commands entered by he user
 * @args: commands entered by user
 * Return: void
 */
void prog_exec(char **args)
{
	for (int i = 0; i < prog_num_builtins(); i++)
	{
		if (strcmp(args[0], progs[i].name) == 0)
		{
			progs[i].func(args);
			return;
		}
	}

	pid_t child_pid = fork();

	if (child_pid == 0)
	{
		execvp(args[0], args);
		exit(1);
	}
	else if (child_pid > 0)
	{
		int status;

		do
		{
			waitpid(child_pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	else
	{
		perror("error: child process failure");
	}
}

/**
 * prog_split_line - this function executes commands
 * Description: this function splits the string into tokens
 * @line: string entered into the shell by the user
 * Return: void
 */

char **prog_split_line(char *line)
{
	int length = 0;
	int capacity = 16;

	char **tokens = malloc(capacity * sizeof(char *));

	if (!tokens)
	{
		perror("error: unable to allocate memory");
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
				perror("error: unable to reallocate memory to tokens");
				exit(1);
			}
		}

		token = strtok(NULL, delimiters);
	}

	tokens[length] = NULL;
	return (tokens);
}

/**
 * prog_read_line - Reads a line
 * Description: reads a single line of input from stdin
 * Return: The return value is a string pointer which needs
 * to be freed once we're finished with it.
 */

char *prog_read_line()
{
	char *line = NULL;
	size_t buflen = 0;
	ssize_t strlen = getline(&line, &buflen, stdin);

	errno = 0;

	if (strlen < 0)
	{
		if (errno)
		{
			perror("error: line not read...");
		}
		exit(1);
	}
	return (line);
}

/**
 * main - executes commands
 *
 * Return: always 0
 */

int main()
{
	while (true)
	{
		printf("#cisfun$ ");
		char *line = prog_read_line();
		char **tokens = prog_split_line(line);

		if (tokens[0] != NULL)
		{
			prog_exec(tokens);
		}

		free(tokens);
		free(line);
		printf("\n");
	}
}
