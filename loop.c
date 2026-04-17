#include "main.h"

/**
 * shell_loop - main loop of the shell
 * @env: environment variables
 *
 * Return: nothing
 */
void shell_loop(char **env)
{
	char *line;
	char **argv;
	char *path;
	size_t len;
	ssize_t nread;
	int direct_path;

	line = NULL;
	len = 0;

	while (1)
	{
		/* Print the prompt only in interactive mode */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		/* Read one line from standard input */
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			break;
		}

		/* Remove the final newline character */
		remove_newline(line);

		/* Skip empty lines */
		if (is_empty_line(line))
			continue;

		/* Split the input line into arguments */
		argv = parse_line(line);
		if (argv == NULL)
			continue;
		if (argv[0] == NULL)
		{
			free_args(argv);
			continue;
		}

		/* Run builtins without creating a child process */
		if (handle_builtin(argv, env, line))
		{
			free_args(argv);
			continue;
		}

		/*
		 * If the command already contains a slash, use it directly.
		 * Otherwise, search for it in PATH.
		 */
		direct_path = contains_slash(argv[0]);
		if (direct_path)
			path = argv[0];
		else
			path = find_command(argv[0]);

		/* If no valid path was found, print an error and continue */
		if (path == NULL)
		{
			write(STDERR_FILENO, "Command not found\n", 18);
			free_args(argv);
			continue;
		}

		/* Execute the command */
		execute_command(path, argv, env);

		/*
		 * Free path only if it was allocated by find_command.
		 * Do not free it when it points directly to argv[0].
		 */
		if (!direct_path)
			free(path);

		/* Free the parsed arguments */
		free_args(argv);
	}
}

/**
 * remove_newline - removes the newline character from a string
 * @line: string to modify
 *
 * Return: nothing
 */
void remove_newline(char *line)
{
	while (*line)
	{
		/* Replace the newline character with the string terminator */
		if (*line == '\n')
		{
			*line = '\0';
			break;
		}
		line++;
	}
}

/**
 * is_empty_line - checks if a line contains only whitespace
 * @line: string to check
 *
 * Return: 1 if the line is empty, 0 otherwise
 */
int is_empty_line(char *line)
{
	while (*line)
	{
		/* If a non-whitespace character is found, the line is not empty */
		if (!(*line == ' ' || *line == '\t'))
			return (0);
		line++;
	}

	return (1);
}
