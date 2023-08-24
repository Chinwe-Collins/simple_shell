#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * do_memory - malloc, free, or free all with a static record
 * @size: the size to malloc if non-0
 * @ptr: the pointer to free if non-NULL
 * Return: the malloc'd pointer if malloc, otherwise the result of free
 */
void *do_memory(size_t size, void *ptr)
{
	static single_list *all;
	void *ret = NULL;
	int i = 0, len = 0;

	if (size)
	{
		ret = malloc(size);
		if (!ret)
			do_exit(2, "malloc failed", EXIT_FAILURE);
		for (i = 0; (unsigned int)i < size; i++)
			((char *)ret)[i] = 0;
		add_list_node_end(&all, ret);
		return (ret);
	}
	else if (ptr)
	{
		len = len_list(all);
		for (i = 0; i < len; i++)
		{
			if (get_list_node_at_index(all, i)->ptr == ptr)
			{
				delete_list_node_at_index(&all, i);
				break;
			}
		}
		free(ptr);
		return (NULL);
	}
	else
	{
		/* If neither size nor ptr, then nuke everything. */
		clear_single_list_all(all);
		return (NULL);
	}
	return (NULL);
}

/**
 * do_exit - custom exit with error message, code, and automatic memory cleanup
 * @fd: the file descriptor to write the message
 * @msg: the message to print
 * @code: the numerical exit code
 */
void do_exit(int fd, char *msg, int code)
{
	if (*msg)
	{
		/* print message */
		write(fd, msg, _strlen(msg));
	}
	/* nuke extra memory */
	do_memory(0, NULL);

	/* exit with code */
	exit(code);
}
