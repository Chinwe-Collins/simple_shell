#include "shell.h"

/**
 * do_env - Get the env, or add a var, or delete a var
 * @add: a variable to add
 * @delete: a variable to delete
 * Return: the current environment after any changes
 */
char **do_env(char *add, char *delete)
{
	static single_list_s *env;
	char *tmp = NULL;
	int len = 0, i = 0, j = 0;

	if (!env)
	{
		env = array_to_list((char **)add);
		return (NULL);
	}
	if (add)
		add_node_end_s(&env, add);
	else if (delete)
	{
		len = list_len(env);
		for (i = 0; i < len; i++)
		{
			j = 0;
			tmp = get_list_node_at_index_s(env, i)->ptr;
			while (delete && tmp && delete[j] && tmp[j] != '=')
			{
				if (delete[j] != tmp[j])
					break;
				j++;
			}
			if (!(delete[j]) && tmp[j] == '=')
			{
				delete_list_node_at_index_s(&env, i);
				break;
			}
		}
	}
	return (list_to_array(env));
}
