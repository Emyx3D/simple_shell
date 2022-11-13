#include "main.h"

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
		char *line = _read_line();
		char **tokens = _split_line(line);

		if (tokens[0] != NULL)
		{
			_exec(tokens);
		}

		free(tokens);
		free(line);
	}

	return (0);
}
