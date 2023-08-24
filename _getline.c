#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * else_handle_input - if buffer does not include \n or EOF
 * @lnptr: the buffer to put the data in
 * @fd: the fd to read from
 * @input: buffer
 * @filled: size of buffer
 * Return: _getline function
 */
ssize_t else_handle_input(char *lnptr, int fd, char *input, int filled)
{
	int red;
	char tmp;

	/* if the buffer is full then read until \n or EOF */
	if (filled == 4096)
	{
		/* should always fill buffer with \n or EOF at end*/
		red = 1;
		while (red && tmp != '\n')
		{
			tmp = 0;
			red = read(fd, &tmp, 1);
		}
		input[4095] = '\n';
		return (_getline(lnptr, fd));
	}
	/* if the buffer isn't full, then fill it and try again. */
	else
	{
		red = read(fd, input + filled, 4096 - filled);
		/* ctrl D was pressed if red is less */
		if (red < (4096 - filled))
			input[filled + red] = '\n';
		filled = filled + red + 1;
		return (_getline(lnptr, fd));
	}
}

/**
 * _getline - reads a number of chars from stdin
 * @lnptr: the buffer to put the data in
 * @fd: the fd to read from
 * Return: the number of bytes read
 */
ssize_t _getline(char *lnptr, int fd)
{
	static char input[4096];
	static int filled;
	int newline_index = -1, i = 0, red = 0;
	ssize_t ret = 0;

	/* if the buffer is empty, fill it */
	if (!filled)
	{
		while ((red = read(fd, input, 4096)) < 0)
		{
			perror("Read Error\n");
			return (-1);
		}
		filled = red;
		if (!red)
			return (0);
	}

	/* if the buffer contains \n or EOF */
	newline_index = has_newline(input);
	if (newline_index != -1)
	{
		for (i = 0; i <= newline_index; i++)
			lnptr[i] = input[i];
		ret = newline_index;
		if (input[ret] == '\n')
			ret = ret + 1;
		/* Shift any remaining chars to the left */
		shiftbuffer(input, newline_index + 1, filled);
		filled = filled - ret;
		return (ret);
	}
	/* if the buffer doesn't contain \n or EOF */
	else
		else_handle_input(lnptr, fd, input, filled);
	return (-1);
}
