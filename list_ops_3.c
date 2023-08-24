#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * list_len - size of a single_list_s
 * @h: struct single_list_s, first node
 * Return: number of nodes
 */
size_t list_len(single_list_s *h)
{
	int i = 0;

	while (h)
	{
		i++;
		h = h->next;
	}
	return (i);
}


/**
 * add_node_s - adds a new node at the beginning of a single_list_s list
 * @head: struct single_list_s, first node
 * @ptr: the pointer data
 * Return: new single_list_s
 */
single_list_s *add_node_s(single_list_s **head, char *ptr)
{
	single_list_s *new = NULL;

	new = do_memory(sizeof(single_list_s), NULL);
	if (!new)
	{
		return (NULL);
	}
	new->ptr = ptr;
	new->next = *head;

	*head = new;
	return (new);
}

/**
 * add_node_end_s - adds a new node at the end of a list_t list
 * @head: struct single_list_s, node
 * @ptr: the pointer data
 * Return: new single_list_s
 */
single_list_s *add_node_end_s(single_list_s **head, char *ptr)
{
	single_list_s *new = NULL, *last = NULL;

	new = do_memory(sizeof(single_list_s), NULL);
	if (!new)
	{
		return (NULL);
	}

	new->ptr = ptr;
	new->next = NULL;

	if (*head == NULL)
	{
		*head = new;
		return (new);
	}

	last = *head;
	while (last->next != NULL)
		last = last->next;

	last->next = new;
	return (new);
}

/**
 * clear_list - frees single_list_s
 * @head: linked list , single_list_s
 */
void clear_list(single_list_s *head)
{
	single_list_s *hold = NULL;

	while (head != NULL)
	{
		hold = head;
		head = head->next;
		do_memory(0, hold);
	}
}

