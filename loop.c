#include "main.h"

/**
 * process_line - parses and executes one command line
 * @line: input line
 * @env: environment variables
 *
 * Return: nothing
 */
static void process_line(char *line, char **env)
{
	char **argv;
	char *path;
	int direct_path;

	argv = parse_line(line);
	if (argv == NULL)
		return;
	if (argv[0] == NULL)
	{
		free_args(argv);
		return;
	}
	if (handle_builtin(argv, env, line))
	{
		free_args(argv);
		return;
	}
	direct_path = contains_slash(argv[0]);
	if (direct_path)
		path = argv[0];
	else
		path = find_command(argv[0]);
	if (path == NULL)
	{
		write(STDERR_FILENO, "Command not found\n", 18);
		free_args(argv);
		return;
	}
	execute_command(path, argv, env);
	if (!direct_path)
		free(path);
	free_args(argv);
}

/**
 * shell_loop - main loop of the shell
 * @env: environment variables
 *
 * Return: nothing
 */
void shell_loop(char **env)
{
	char *line;
	size_t len;
	ssize_t nread;

	line = NULL;
	len = 0;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			break;
		}
		remove_newline(line);
		if (is_empty_line(line))
			continue;
		process_line(line, env);
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
		if (!(*line == ' ' || *line == '\t'))
			return (0);
		line++;
	}
	return (1);
}
