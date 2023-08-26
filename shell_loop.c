#include "shell.h"
#include <stdio.h>
#include <signal.h>

/**
 * handle_signal - writes new line plus prompt
 * @signal: signal
 */
void handle_signal(int signal)
{
	(void) signal;

	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, "#cisfun$ ", 9);
}
/**
 * handle_file - parses through list of commands in a file and executes
 * @filename: name of file with commands to parse through and execute
 */
void handle_file(char *filename)
{
	char *buff = NULL;
	char **tokens = NULL;
	char *copy_buffer = NULL;
	int i, newline_index;

	/* read file and write commands to a buff */
	buff = do_memory(4096, NULL);
	buff = read_textfile(filename);

	/* separate commands in file */
	newline_index = has_newline(buff);
	copy_buffer = do_memory(4096, NULL);
	while (newline_index)
	{
		for (i = 0; i < newline_index; i++)
		{
			copy_buffer[i] = buff[i];
		}
		copy_buffer[i] = '\0';
		/* tokenize individual commands */
		tokens = _strtok(copy_buffer, " ");
		/* execute commands */
		execute(tokens);
		clear_double_array(tokens);
		copy_buffer = _memset(copy_buffer, '\0', newline_index);
		shiftbuffer(buff, newline_index + 1, 4096);
		newline_index = has_newline(buff);
	}
	do_memory(0, buff);
}

/**
 * shell_loop - reads STDIN, tokenizes it and executes command
 *  @filename: if argv[1] exist takes in filename
 */
void shell_loop(char *filename)
{
	char *buff = NULL, **tokens = NULL, *delim = " \n";
	int code = 0;
	ssize_t lgetline = 0, buffsize = 4096;

	if (filename)
		handle_file(filename);
	else
	{
		while (1)
		{/* only print a prompt if isatty is true */
			if (isatty(STDIN_FILENO))
				write(STDERR_FILENO, "#cisfun$ ", 9);
			buff = do_memory(buffsize, NULL);
			/* read command, getline and check if it fails */
			while ((lgetline = _getline(buff, STDIN_FILENO)) < 0)
			{
				do_memory(0, buff);
				do_exit(2, "", -1);
			}
			if (lgetline == 0)/* exit if ctrl- d */
			{
				if (isatty(STDIN_FILENO))
					write(STDERR_FILENO, "\n", 1);
				do_exit(2, "", code);
			}
			if (buff[lgetline - 1] != '\n') /* if ctrl- d and some text */
			{
				do_memory(0, buff);
				continue;
			}
			if ((_strcmp(buff, "exit\n")) == 0) /* check for exit command */
				do_exit(2, "", code);
			tokens = _strtok(buff, delim); /* tokenize STDIN */
			code = execute(tokens);
			do_memory(0, buff);
			clear_double_array(tokens);
			lnum(1);
		}
	}
}
