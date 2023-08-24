#include "shell.h"
#include <stdio.h>

/**
 * exec_single - execute a single command
 * @tokens: the tokens for a single command
 * Return: int return value of the exec
 */
int exec_single(char **tokens)
{
	char **btins = NULL;
	int works = 1, i = 0, check_btin = 0;

	if (!tokens || !tokens[0])
		return (0);
	btins = get_btin();
	/* check if its a builtin */
	for (i = 0; btins[i]; i++)
		if (_strcmp(btins[i], tokens[0]) == 0)
		{
			check_btin = i + 1;
			break;
		}

	if (check_btin && tokens)
		works = exec_btin(tokens, check_btin);
	else if (tokens)
		works = exec_nbtin(tokens);
	return (works);
}

/**
 * get_next_commands - gets the tokens after the first && || or ;
 * @tokens: the tokens for the current command segment
 * Return: the tokens after the first && || ;, or NULL
 */
char **get_next_commands(char **tokens)
{
	char **extokens = NULL;
	int cmd_size = 0, retSize = 0, i = 0;

	if (!tokens || !(tokens[0]))
		return (NULL);
	cmd_size = sizeof_cmd(tokens);
	if (!(tokens[cmd_size]) || !(tokens[cmd_size + 1]))
		return (NULL);
	while (tokens[cmd_size + 1 + retSize])
		retSize++;

	extokens = do_memory(sizeof(char *) * (retSize + 1), NULL);
	for (i = 0; i < retSize; i++)
	{
		extokens[i] = do_memory(_strlen(tokens[cmd_size + 1 + i]) + 1, NULL);
		_strcpy(extokens[i], tokens[cmd_size + 1 + i]);
	}
	extokens[i] = NULL;
	return (extokens);
}

/**
 * get_current_command - gets the command before && || or ;
 * @tokens: the tokens for the current command segment
 * Return: the command up until the first occurence of && || ; or NULL
 */
char **get_current_command(char **tokens)
{
	char **extokens = NULL;
	int cmd_size = 0, i = 0;

	if (!tokens || !(tokens[0]))
		return (NULL);
	/* split tokens into separate commands if ;,&&,|| exist */
	cmd_size = sizeof_cmd(tokens);
	if (!cmd_size)
		return (NULL);
	extokens = do_memory(sizeof(char *) * (cmd_size + 1), NULL);
	for (i = 0; i < cmd_size; i++)
	{
		extokens[i] = do_memory(_strlen(tokens[i]) + 1, NULL);

		_strcpy(extokens[i], tokens[i]);
	}
	extokens[i] = NULL;

	return (extokens);
}

/**
  * execute - main execute function
  * @tokens: STDIN tokenized
  * Return: int if succesful
  */
int execute(char **tokens)
{
	int works = 0, op = 0;
	char **head = NULL;
	char **tail = NULL;

	op = search_funcs(tokens);
	head = get_current_command(tokens);
	tail = get_next_commands(tokens);

	while (1)
	{
		if (!head || !(head[0]))
			return (works);

		works = exec_single(head);

		if (op == 3 && !works)
			return (works);
		if (op == 2 && works)
			return (works);

		op = search_funcs(tail);
		head = get_current_command(tail);
		tail = get_next_commands(tail);

	}
	return (1);
}
