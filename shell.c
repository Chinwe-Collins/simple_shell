#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


/**
 * lnum - get current line number and/or add to it
 * @add: if not zero, add this amt
 * Return: the line number
 */
int lnum(int add)
{
	static int line;

	line = line + add;
	return (line);
}

/**
 * get_program_name - gets the program name
 * @name: the name of the prog (first execution)
 * Return: the name of the program
 */
char *get_program_name(char *name)
{
	static char *ret;

	if (!ret)
	{
		ret = name;
	}
	return (ret);
}

/**
 * print_error - custom error printing
 * @command: the message to print
 * @status: the type of error to print
 * @extra: any extra text
 */
void print_error(char *command, int status, char *extra)
{
	char *name = NULL;
	char *line = NULL;
	char *msg = NULL;

	name = get_program_name(NULL);
	line = _itoa(lnum(0));
	write(STDERR_FILENO, name, _strlen(name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, line, _strlen(line));

	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": ", 2);

	switch (status)
	{
	case 2:
		msg = "No such file or directory";
		break;
	case 126:
		msg = "Permission denied";
		break;
	case 127:
		msg = "not found";
		break;
	case 9000:
		/* exit illegal number should exit with a code of 2*/
		msg = "Illegal number: ";
		break;
	default:
		msg = "Unknown error occured.";
	}
	write(STDERR_FILENO, msg, _strlen(msg));

	if (extra)
		write(STDERR_FILENO, extra, _strlen(extra));

	write(STDERR_FILENO, "\n", 1);
}


/**
  * main - simple shell
  * @argc: Number of arguments
  * @argv: list of arguments
  * @envp: environment
  * Return: 0 if successful
  */
int main(int argc, char **argv, char **envp)
{
	char *filename = NULL;

	get_program_name(argv[0]);

	/* argc the right amount of arguments */
	if (argc > 2)
		return (-1);

	/* check if argv[1] is a file */
	if (argv && argv[1])
		filename = argv[1];
	/* signal handler */
	signal(SIGINT, handle_signal);
	/* initialize the environment */
	do_env((char *)envp, NULL);

	/* initialize the lnum */
	lnum(1);

	/* read, tokenize, execute loop */
	shell_loop(filename);

	/* clean up */

	return (0);
}
