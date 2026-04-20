#include "main.h"

/**
 * main - entry point of the shell
 * @ac: number of arguments
 * @av: array of arguments
 * @env: environment variables
 *
 * Return: exit status of the shell loop
 */
int main(int ac, char **av, char **env)
{
	/* ac is not used in this file */
	(void)ac;

	/* return the exit status of the main shell loop */
	return (shell_loop(env, av[0]));
}
