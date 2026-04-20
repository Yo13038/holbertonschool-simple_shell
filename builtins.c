#include "main.h"

/**
 * handle_builtin - checks if a command is a builtin and executes it
 * @argv: array of arguments
 * @env: environment variables
 * @line: input line
 * @status: builtin status output
 *
 * Return: 1 if a builtin was executed, 0 otherwise
 */
int handle_builtin(char **argv, char **env, char *line, int *status)
{
	if (argv == NULL || argv[0] == NULL)
		return (0);
	if (_strcmp(argv[0], "exit") == 0)
	{
		builtin_exit(argv, line, *status);
		return (1);
	}
	if (_strcmp(argv[0], "env") == 0)
	{
		*status = builtin_env(env);
		return (1);
	}
	return (0);
}

/**
 * builtin_exit - exits the shell
 * @argv: array of arguments
 * @line: input line
 * @status: builtin status output
 *
 * Return: nothing
 */
void builtin_exit(char **argv, char *line, int status)
{
	free_args(argv);
	free(line);
	exit(status);
}

/**
 * builtin_env - prints the current environment
 * @env: environment variables
 *
 * Return: 0 on success
 */
int builtin_env(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
		printf("%s\n", env[i]);
	return (0);
}
