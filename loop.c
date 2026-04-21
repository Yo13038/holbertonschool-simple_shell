#include "main.h"

/**
 * print_error_message - prints a shell-style error message
 * @prog_name: shell program name
 * @count: command counter
 * @command: command that caused the error
 * @message: error message to display
 *
 * Return: nothing
 */
static void print_error_message(char *prog_name, int count,
	char *command, char *message)
{
	char buffer[12];
	int i;
	int len;

	i = 10;
	buffer[11] = '\0';
	if (count == 0)
		buffer[i--] = '0';
	while (count > 0)
	{
		buffer[i--] = (count % 10) + '0';
		count /= 10;
	}
	write(STDERR_FILENO, prog_name, _strlen(prog_name));
	write(STDERR_FILENO, ": ", 2);
	len = 10 - i;
	write(STDERR_FILENO, &buffer[i + 1], len);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, message, _strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

/**
 * process_line - parses and executes one command line
 * @line: input line
 * @env: environment variables
 * @prog_name: shell program name
 * @count: command counter
 * @last_status: status of the last executed command
 *
 * Return: command status
 */
static int process_line(char *line, char **env,
	char *prog_name, int count, int last_status)
{
	char **argv, *path;
	int direct_path, status;

	/* Keep the previous status unless a new command changes it */
	status = last_status;
	argv = parse_line(line);
	if (argv == NULL)
		return (1);
	if (handle_builtin(argv, env, line, &status))
	{
		free_args(argv);
		return (status);
	}
	direct_path = contains_slash(argv[0]);
	if (direct_path && access(argv[0], F_OK) != 0)
	{
		print_error_message(prog_name, count, argv[0], "not found");
		free_args(argv);
		return (127);
	}
	if (direct_path && !is_executable_command(argv[0]))
	{
		print_error_message(prog_name, count, argv[0], "Permission denied");
		free_args(argv);
		return (126);
	}
	path = direct_path ? argv[0] : find_command(argv[0]);
	if (path == NULL)
	{
		print_error_message(prog_name, count, argv[0], "not found");
		free_args(argv);
		return (127);
	}
	status = execute_command(path, argv, env);
	if (!direct_path)
		free(path);
	free_args(argv);
	return (status);
}

/**
 * shell_loop - main loop of the shell
 * @env: environment variables
 * @prog_name: shell program name
 *
 * Return: last command status
 */
int shell_loop(char **env, char *prog_name)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int count = 0;
	int status = 0;

	while (1)
	{
		/* Print the prompt only in interactive mode */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			break;
		}
		count++;
		remove_newline(line);
		if (is_empty_line(line))
			continue;
		status = process_line(line, env, prog_name, count, status);
	}
	return (status);
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
		/* Stop the string at the newline added by getline */
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
		/* Any non-space/tab character means the line is not empty */
		if (!(*line == ' ' || *line == '\t'))
			return (0);
		line++;
	}
	return (1);
}
