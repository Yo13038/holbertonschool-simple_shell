#include "main.h"

/**
 * free_args - frees memory allocated for an arguments array
 * @argv: array of arguments to free
 *
 * Return: nothing
 */
void free_args(char **argv)
{
	int i;

	/* Nothing to free if argv is NULL*/
	if (argv == NULL)
		return;

	/* Free each duplicated argument string */
	for (i = 0; argv[i] != NULL; i++)
		free(argv[i]);

	/* Free the array of pointers itself */
	free(argv);
}
