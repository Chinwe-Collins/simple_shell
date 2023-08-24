#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * clear_single_list_all - frees single_list and all contained pointers
 * @head: linked list , single_list
 */
void clear_single_list_all(single_list *head)
{
	single_list *hold = NULL;

	while (head != NULL)
	{
		hold = head;
		head = head->next;
		free(hold->ptr);
		free(hold);
	}
}

/**
 * get_list_node_at_index - return nth node of a linked list
 * @head: pointer to the start of linked list
 * @index: index
 * Return: the nth node
 */
single_list *get_list_node_at_index(single_list *head, unsigned int index)
{
	unsigned int i = 0;

	for (i = 0; head; i++, head = (*head).next)
		if (i == index)
			return (head);
	return (NULL);
}

/**
 * insert_list_node_at_index - inserts a new node at a given position
 * @head: pointer to the beginning of linked list
 * @index: index where to insert
 * @ptr: value for ptr
 * Return: address of new node or NULL if fails
 */
single_list *insert_list_node_at_index(single_list **head,
		unsigned int index, void *ptr)
{
	single_list *new = NULL, *hold = *head;
	unsigned int i = 0;

	if (!index)
	{
		new = malloc(sizeof(single_list));
		if (!new)
			return (NULL);

		(*new).ptr = ptr;
		(*new).next = *head;

		*head = new;

		return (*head);
	}

	while (hold)
	{
		if (i == (index - 1))
		{
			new = malloc(sizeof(single_list));
			if (!new)
				return (NULL);
			(*new).ptr = ptr;
			(*new).next = (*hold).next;
			(*hold).next = new;
			return (new);
		}
		hold = (*hold).next;
		i++;
	}
	return (NULL);
}

/**
 * delete_list_node_at_index - deletes a node at a given position
 * @head: pointer to the beginning of linked list
 * @index: index to be deleted
 * Return: 1 if succesful -1 if fails
 */
int delete_list_node_at_index(single_list **head, unsigned int index)
{
	single_list *hold = NULL, *delete = NULL;
	unsigned int i = 0, action = 0;

	if (!*head)
		return (-1);
	for (i = 0, hold = *head; hold && index; i++, hold = (*hold).next)
		if (i == (index - 1))
		{
			action = 1;
			break;
		}

	if (action)
	{
		delete = (*hold).next;
		(*hold).next = (*delete).next;
		free(delete);
		return (1);
	}
	else if (!index && (**head).next)
	{
		delete = *head;
		*head = (*delete).next;
		free(delete);
		return (1);
	}
	else if (!index && *head)
	{
		*head = NULL;
		free(*head);
		return (1);
	}
	return (-1);
}

