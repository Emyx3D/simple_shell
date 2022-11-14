#include "main.h"

/**
 * prog_exit -  function to exit shell
 * @args: exit arguments in the shell
 * Description: if the command entered in the shell is "exit"
 * then, the shell program ends
 * Return: void
 */
void prog_exit(char **args)
{
	exit(0);
}

/**
 * prog_cd -  funftion changes current directory
 * @args: the directory to be changed to
 * Description: changes the current working
 * directory to another stated in args
 * Return: void
 */

void prog_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "collins: cd: missing argument\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("collins: cd");
		}
	}
}

/**
 * prog_help - function to use help command
 * Description: displays help text
 * @args: argument entered into the shell by user
 * Return: void
 */
void prog_help(char **args)
{
	char *helptext =
	    "Simple_shell - the Kinda Aimless Shell\n."
	    "The following commands are built in: \n"
	    "  cd       Change the working directory.\n"
	    "  exit     Exit the shell.\n"
	    "  help     Print this help text.\n";
	printf("%s", helptext);
}
