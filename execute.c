#include "main.h"

/**
 * execute_command - Executes a command in a child process.
 * @path: Full path of the executable (e.g., /bin/ls).
 * @argv: Array of arguments (e.g., {"/bin/ls", "-l", NULL}).
 * @env: System environment variables.
 *
 * Return: 1 on success, -1 on failure.
 */
int execute_command(char *path, char **argv, char **env)
{
	pid_t child_pid;
	int status;

	/* Check if input pointers are valid */
	if (argv == NULL || path == NULL)
		return (-1);

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Fork Error");
		return (-1);
	}

	if (child_pid == 0)
	{
		/* Child process: Try to execute the command */
		if (execve(path, argv, env) == -1)
		{
			/* If execve fails, print error and exit child process */
			perror("Error");
			/*127 is commonly used to indicate "command not found" */
			exit(127);
		}
	}
	else
	{
		/* PARENT PROCESS: Wait for child to terminate */
		wait(&status);
	}

	return (1);
}
