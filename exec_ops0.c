#include "shell.h"
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

/**
  * exec_btin - execute function for builtin
  * @tokens: STDIN tokenized
  * @btin_to_exec: which builtin to execute
  * Return: 0 if succesful 1 if it fails
  */
int exec_btin(char **tokens, int btin_to_exec)
{
	int exit = 0;
	int i = 0;

	switch (btin_to_exec)
	{
	case 1:
	{
		if (tokens[1])
		{
			for (; tokens[1][i]; i++)
				if (!_isdigit(tokens[1][i]))
				{
					do_exit(2, "numeric arguments only\n", exit);
				}
			exit = _atoi(tokens[1]);
		}
		do_exit(2, "", exit);
		break;
	}
	case 2:
		return (cd_btin(tokens));
	case 3:
		return (env_btin());
	case 4:
		return (setenv_btin(tokens));
	case 5:
		return (unsetenv_btin(tokens));
	}
	return (0);
}

/**
 * check_access - checks if path exists or if permission exists for command
 * @cmd: path to command
 * @token: command
 * Return: exit condition
 */
int check_access(char *cmd, char *token)
{
	int access_code = 0;
	/* check if path exists */
	access_code = access(cmd, F_OK);
	if (access_code)
	{
		/* not found */
		print_error(token, 2, NULL);
		return (2);
	}
	/* check if path is exucatable */
	access_code = access(cmd, X_OK);
	if (access_code)
	{
		/* Permission denied */
		print_error(token, 126, NULL);
		return (126);
	}
	return (0);
}

/**
 * prep_execve - preps cmd by checking current path and then the PATH for cmd
 * @token: commmand to check
 * Return: command preped for execve
 */
char *prep_execve(char *token)
{
	char **envs = NULL;
	char *cmd = NULL;
	char *cwd = NULL;
	char *path = NULL;
	int access_code = 0;

	cwd = do_memory(100, NULL);
	cmd = get_full_command(cwd, token);
	access_code = access(cmd, F_OK);
	if (access_code)
	{
		envs = _get_path();
		path = _find_path(envs, token);
		cmd = get_full_command(path, token);
		clear_double_array(envs);
	}
	return (cmd);
}
/**
  * exec_nbtin - execute function for non btins
  * @tokens: STDIN tokenized
  * Return: the exit status of the program, 0 if successful
  */
int exec_nbtin(char **tokens)
{
	char *cmd = NULL;
	pid_t cpid, wid;
	int status = 0, access_code = 0;

	cmd = prep_execve(tokens[0]);
	while ((access_code = check_access(cmd, tokens[0])))
		return (access_code);
	/* fork and exec */
	cpid = fork();
	/* Fork failed - exits with error message and exit code */
	if (cpid == -1)
		do_exit(2, "Fork failed", EXIT_FAILURE);
	if (!cpid)/* child */
	{
		execve(cmd, tokens, (char * const *)get_environs());
		perror("");
		do_exit(2, "Couldn't exec", EXIT_FAILURE);
	}
	else/* parent */
	{
		do {
			wid = waitpid(cpid, &status, WUNTRACED);
			if (wid == -1)
			{
				perror("waitpid");
				do_exit(STDERR_FILENO, "", EXIT_FAILURE);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		do_memory(0, cmd);
	}
	return (status);
}

/**
  * search_funcs - search for ;, &&, || operators
  * @tokens: tokens from std input
  * Return: 0 if none, 1 if ';', 2 if '&&' 3 if '||'
  */
int search_funcs(char **tokens)
{
	int i = 0;

	if (!tokens)
	{
		return (0);
	}
	for (i = 0; tokens[i]; i++)
	{
		/* check for ;, &&, || */
		if (tokens[i][0] == ';')
			return (1);
		if (tokens[i][0] == '&' && tokens[i][1] && tokens[i][1] == '&')
			return (2);
		if (tokens[i][0] == '|' && tokens[i][1] && tokens[i][1] == '|')
			return (3);
	}
	return (0);
}
