#include "main.h"

/**
 * handle_builtin - checks if a command is a builtin and executes it
 * @argv: array of arguments
 * @env: environment variables
 * @line: input line
 *
 * Return: 1 if a builtin was executed, 0 otherwise
 */
int handle_builtin(char **argv, char **env, char *line)
{
	/* If argv is invalid, it cannot be a builtin */
	if (argv == NULL || argv[0] == NULL)
		return (0);

	/* Check if the command is "exit" */
	if (_strcmp(argv[0], "exit") == 0)
	{
		builtin_exit(argv, line);
		return (1);
	}

	/* Check if the command is "env" */
	if (_strcmp(argv[0], "env") == 0)
	{
		builtin_env(env);
		return (1);
	}

	/* The command is not a builtin */
	return (0);
}

/**
 * builtin_exit - exits the shell
 * @argv: array of arguments
 * @line: input line
 *
 * Return: nothing
 */
void builtin_exit(char **argv, char *line)
{
	/* Free the parsed arguments before exiting */
	free_args(argv);

	/* Free the input line buffer */
	free(line);

	/* Exit the shell with status 0 */
	exit(0);
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

	/* Print each environment variable on its own line */
	for (i = 0; env[i] != NULL; i++)
		printf("%s\n", env[i]);

	return (0);
}
