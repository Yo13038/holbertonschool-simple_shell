#include "main.h"

/**
 * execute_command - executes a command in a child process
 * @path: full path of the executable
 * @argv: array of arguments
 * @env: environment variables
 *
 * Return: child exit status, or 1 on internal failure
 */
int execute_command(char *path, char **argv, char **env)
{
	pid_t child_pid;
	int status;

	/* Reject invalid execution data */
	if (path == NULL || argv == NULL || argv[0] == NULL)
		return (1);

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return (1);
	}

	/* Replace the child process image with the requested program */
	if (child_pid == 0)
	{
		if (execve(path, argv, env) == -1)
		{
			perror(argv[0]);
			exit(127);
		}
	}

	/* Wait for the specific child and return its status */
	if (waitpid(child_pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
