#include "main.h"

/**
 * main - entry point of the shell
 * @ac: number of arguments
 * @av: array of arguments
 * @env: environment variables
 *
 * Return: Always 0
 */
int main(int ac, char **av, char **env)
{
	/* ac and av are not used in this file */
	(void)ac;
	(void)av;

	/* Start the main shell loop */
	shell_loop(env);

	return (0);
}
