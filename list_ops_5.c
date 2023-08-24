#include "shell.h"

/**
 * list_to_array - copy a char * linked list into a char **
 * @head: the head of the linked list
 * Return: a malloc'd char **
 */
char **list_to_array(single_list_s *head)
{
	char **ret = NULL;
	char *tmp = NULL;
	char *tmp2 = NULL;
	int len = 0, i = 0;

	len = list_len(head);
	ret = do_memory(sizeof(char *) * (len + 1), NULL);
	for (i = 0; i < len; i++)
	{
		tmp2 = get_list_node_at_index_s(head, i)->ptr;
		tmp = do_memory(sizeof(char) * (_strlen(tmp2) + 1), NULL);
		tmp = _strcat(tmp, tmp2);
		ret[i] = tmp;
	}
	ret[i] = NULL;
	return (ret);
}

/**
 * array_to_list - copy a char ** array into a malloc'd char * linked list
 * @arr: the char **
 * Return: a malloc'd char * linked list
 */
single_list_s *array_to_list(char **arr)
{
	single_list_s *ret = NULL;
	char *tmp = NULL;
	int i = 0;

	while (arr[i])
	{
		tmp = do_memory(sizeof(char) * (_strlen(arr[i]) + 1), NULL);
		tmp = _strcat(tmp, arr[i]);
		add_node_end_s(&ret, tmp);
		i++;
	}
	return (ret);
}


/**
 * clear_double_array - free a double char pointer
 * @list: the double char pointer
 */
void clear_double_array(char **list)
{
	int i = 0;

	for (i = 0; list[i]; i++)
		do_memory(0, list[i]);
	do_memory(0, list);
}

