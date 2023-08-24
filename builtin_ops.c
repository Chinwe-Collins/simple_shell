#include "shell.h"

/**
  * get_btin - list of builtin commands
  * Return: double pointer holding list of commands
  */
char **get_btin()
{
	char **btin;

	btin = do_memory(sizeof(char *) * 6, NULL);

	btin[0] = "exit";
	btin[1] = "cd";
	btin[2] = "env";
	btin[3] = "setenv";
	btin[4] = "unsetenv";
	btin[5] = NULL;

	return (btin);
}

/**
 * env_btin - Lists environment
 *  Return: 0 if successfull
 */
int env_btin(void)
{
	char **env;
	int i = 0, len = 0;

	env = get_environs();
	while (env[i])
	{
		len = _strlen(env[i]);
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i = i + 1;
	}
	clear_double_array(env);

	return (0);
}

/**
 * setenv_btin - Set an environment variable
 * @tokens: the tokens for the command
 * Return: the return code
 */
int setenv_btin(char **tokens)
{
	char *ret = NULL;

	if (!tokens[1] || !tokens[2])
	{
		print_error(tokens[0], 3001, NULL);
		return (1);
	}
	do_env(NULL, tokens[1]);

	ret = do_memory(_strlen(tokens[1]) + _strlen(tokens[2]) + 2, NULL);
	_strcat(ret, tokens[1]);
	_strcat(ret, "=");
	_strcat(ret, tokens[2]);
	do_env(ret, NULL);

	return (0);
}

/**
 * unsetenv_btin - Unset an environment variable
 * @tokens: the tokens for the command
 * Return: the return code
 */
int unsetenv_btin(char **tokens)
{

	if (!tokens[1])
	{
		print_error(tokens[0], 3002, NULL);
		return (1);
	}
	do_env(NULL, tokens[1]);

	return (0);
}


/**
 * cd_btin - executes cd function, changes directory
 * @tokens: command input into prompt tokenized
 * Return: the exit status
 */
int cd_btin(char **tokens)
{
	char *HOME = NULL, *temp;
	static char *lstdir;

	(void)HOME;
	if (!lstdir)
		lstdir = do_memory(100, NULL);
	temp = do_memory(100, NULL);
	if (tokens[1] && _strcmp(tokens[1], "-") == 0)
	{
		/* go to previous directory */
		getcwd(temp, 100);
		chdir(lstdir);
		write(STDOUT_FILENO, lstdir, _strlen(lstdir));
		write(STDOUT_FILENO, "\n", 1);
		lstdir = temp;
	}
	else if (tokens[1])
	{
		/* change directory to tokens[1] */
		getcwd(lstdir, 100);
		chdir(tokens[1]);
	}
	else
	{
		/* change to home directory */
		getcwd(lstdir, 100);
		chdir(get_env_value("HOME"));
	}
	return (0);
}
