#include "main.h"
/**
 * parse_line - Splits a string into an array of tokens (arguments).
 * @line: The string to be parsed.
 *
 * Return: A NULL-terminated array of strings, or NULL on failure.
 */
char **parse_line(char *line)
{
	char **argv;
	char *token;
	int i = 0, count = 0;
	char *line_copy;

	if (line == NULL)
		return (NULL);
	/* count the number of tokens to know how much memory to allocate */
	/* use a copy because strtok modifies the string */
	line_copy = _strdup(line);
	token = strtok(line_copy, " \t\n\r");
	while (token)
	{
		count++;
		token = strtok(NULL, " \t\n\r");
	}
	free(line_copy);
	/* allocate the array of pointers (+1 for the NULL) */
	argv = malloc(sizeof(char *) * (count + 1));
	if (argv == NULL)
		return (NULL);
	/* split the line and fill the array */
	token = strtok(line, " \t\n\r");
	while (token)
	{
		/* duplicate each token to ensure it has its own memory space */
		argv[i] = _strdup(token);
		if (argv[i] == NULL)
		{
			/* If one allocation fails, free everything before */
			free_args(argv);
			return (NULL);
		}
		token = strtok(NULL, " \t\n\r");
		i++;
	}
	argv[i] = NULL; /* end with NULL because of execve*/

	return (argv);
}
