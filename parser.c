#include "main.h"

/**
 * count_tokens - counts the number of tokens in a line
 * @line: line to scan
 *
 * Return: number of tokens
 */
static int count_tokens(char *line)
{
	char *copy;
	char *token;
	int count;

	/* Duplicate the line because strtok modifies the string */
	copy = _strdup(line);
	if (copy == NULL)
		return (0);

	count = 0;
	token = strtok(copy, " \t\n\r");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " \t\n\r");
	}
	free(copy);
	return (count);
}

/**
 * free_partial_args - frees partially allocated argv entries
 * @argv: array of arguments
 * @count: number of allocated entries
 *
 * Return: nothing
 */
static void free_partial_args(char **argv, int count)
{
	/* Free only the entries that were successfully allocated */
	while (count > 0)
	{
		count--;
		free(argv[count]);
	}
	free(argv);
}

/**
 * parse_line - splits a string into an array of tokens
 * @line: string to parse
 *
 * Return: a NULL-terminated array of strings, or NULL on failure
 */
char **parse_line(char *line)
{
	char **argv;
	char *token;
	int count;
	int i;

	if (line == NULL)
		return (NULL);
		/* Count tokens before allocating argv */
	count = count_tokens(line);
	if (count == 0)
		return (NULL);

	argv = malloc(sizeof(char *) * (count + 1));
	if (argv == NULL)
		return (NULL);

	i = 0;
	token = strtok(line, " \t\n\r");
	while (token != NULL)
	{
		/* Duplicate each token so argv owns its memory */
		argv[i] = _strdup(token);
		if (argv[i] == NULL)
		{
			free_partial_args(argv, i);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \t\n\r");
	}
	/* End the array with NULL for execve */
	argv[i] = NULL;
	return (argv);
}
