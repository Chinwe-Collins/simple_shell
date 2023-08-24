#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * clear_list_all - frees single_list_s and all contained pointers
 * @head: linked list , single_list_s
 */
void clear_list_all(single_list_s *head)
{
	single_list_s *hold = NULL;

	while (head != NULL)
	{
		hold = head;
		head = head->next;
		do_memory(0, hold->ptr);
		do_memory(0, hold);
	}
}

/**
 * get_list_node_at_index_s - return nth node of a linked list
 * @head: pointer to the start of linked list
 * @index: index
 * Return: the nth node
 */
single_list_s *get_list_node_at_index_s(single_list_s *head,
		unsigned int index)
{
	unsigned int i = 0;

	for (i = 0; head; i++, head = (*head).next)
		if (i == index)
			return (head);
	return (NULL);
}

/**
 * insert_list_node_at_index_s - inserts a new node at a given position
 * @head: pointer to the beginning of linked list
 * @index: index where to insert
 * @ptr: value for ptr
 * Return: address of new node or NULL if fails
 */
single_list_s *insert_list_node_at_index_s(single_list_s **head,
		unsigned int index, char *ptr)
{
	single_list_s *new = NULL, *hold = *head;
	unsigned int i = 0;

	if (!index)
	{
		new = do_memory(sizeof(single_list_s), NULL);
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
			new = do_memory(sizeof(single_list_s), NULL);
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
 * delete_list_node_at_index_s - deletes a node at a given position
 * @head: pointer to the beginning of linked list
 * @index: index to be deleted
 * Return: 1 if succesful -1 if fails
 */
int delete_list_node_at_index_s(single_list_s **head, unsigned int index)
{
	single_list_s *hold = NULL, *delete = NULL;
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
		do_memory(0, delete);
		return (1);
	}
	else if (!index && (**head).next)
	{
		delete = *head;
		*head = (*delete).next;
		do_memory(0, delete);
		return (1);
	}
	else if (!index && *head)
	{
		*head = NULL;
		do_memory(0, *head);
		return (1);
	}
	return (-1);
}

