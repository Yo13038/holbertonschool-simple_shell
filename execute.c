#include "main.h"
/**
 * execute_command - Executes a command in a child process.
 * @path: Full path of the executable (e.g., /bin/ls).
 * @argv: Array of arguments (e.g., {"ls", "-l", NULL}).
 * @env: System environment variables.
 *
 * Return: 1 on success, -1 on failure.
 */
int execute_command(char *path, char **argv, char **env)
{
	pid_t child_pid;
	int status;

	/* Basic validation of inputs */
	if (path == NULL || argv == NULL || argv[0] == NULL)
		return (-1);

	child_pid = fork();

	if (child_pid == -1)
	{
		/* Fork failed */
		perror("Fork Error");
		return (-1);
	}

	if (child_pid == 0)
	{
		/* CHILD PROCESS */
		/* path is the full path found by find_command or provided directly */
		if (execve(path, argv, env) == -1)
		{
			perror("Error");
			/* Exit child process with error code */
			exit(127);
		}
	}
	else
	{
		/* PARENT PROCESS */
		/* Wait for the specific child process to finish */
		wait(&status);
	}

	return (1);
}