#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * len_list - size of a single_list
 * @h: struct single_list, first node
 * Return: number of nodes
 */
size_t len_list(single_list *h)
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
 * add_list_node - adds a new node at the beginning of a single_list list
 * @head: struct single_list, first node
 * @ptr: the pointer data
 * Return: new single_list
 */
single_list *add_list_node(single_list **head, void *ptr)
{
	single_list *new = NULL;

	new = malloc(sizeof(single_list));
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
 * add_list_node_end - adds a new node at the end of a single_list list
 * @head: struct single_list, node
 * @ptr: the pointer data
 * Return: new single_list
 */
single_list *add_list_node_end(single_list **head, void *ptr)
{
	single_list *new = NULL, *last = NULL;

	new = malloc(sizeof(single_list));
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
 * clear_single_list - frees single_list
 * @head: linked list , single_list
 */
void clear_single_list(single_list *head)
{
	single_list *hold = NULL;

	while (head != NULL)
	{
		hold = head;
		head = head->next;
		free(hold);
	}
}

