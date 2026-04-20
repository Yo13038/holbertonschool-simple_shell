#include "main.h"

/**
 * _getenv - searches the environment list for a variable
 * @name: name of the environment variable
 *
 * Return: pointer to the value after '=', or NULL if not found
 */
char *_getenv(const char *name)
{
	int i;
	int len;

	if (environ == NULL || name == NULL)
		return (NULL);
	i = 0;
	len = _strlen((char *)name);
	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], (char *)name, len) == 0 &&
		    environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

/**
 * contains_slash - checks if a command contains a slash
 * @command: command string
 *
 * Return: 1 if a slash is found, 0 otherwise
 */
int contains_slash(char *command)
{
	int i;

	if (command == NULL)
		return (0);

	i = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

/**
 * build_path - builds a full path from a directory and a command
 * @dir: directory path
 * @cmd: command name
 *
 * Return: allocated full path, or NULL on failure
 */
char *build_path(char *dir, char *cmd)
{
	char *path;
	int len_dir;
	int len_cmd;

	if (dir == NULL || cmd == NULL)
		return (NULL);

	len_dir = _strlen(dir);
	len_cmd = _strlen(cmd);
	path = malloc(sizeof(char) * (len_dir + len_cmd + 2));
	if (path == NULL)
		return (NULL);

	_strcpy(path, dir);
	path[len_dir] = '/';
	_strcpy(path + len_dir + 1, cmd);
	return (path);
}

/**
 * is_executable_command - checks if a path is a regular executable file
 * @path: full path to check
 *
 * Return: 1 if executable, 0 otherwise
 */
int is_executable_command(char *path)
{
	struct stat st;

	if (path == NULL)
		return (0);
	if (stat(path, &st) != 0)
		return (0);
	if (!S_ISREG(st.st_mode))
		return (0);
	if (access(path, X_OK) != 0)
		return (0);
	return (1);
}

/**
 * find_command - locates a command in PATH
 * @command: command name
 *
 * Return: allocated full path, or NULL if not found
 */
char *find_command(char *command)
{
	char *path_env;
	char *path_copy;
	char *token;
	char *full_path;

	if (command == NULL)
		return (NULL);
	if (contains_slash(command))
		return (is_executable_command(command) ? _strdup(command) : NULL);

	path_env = _getenv("PATH");
	if (path_env == NULL)
		return (NULL);
	path_copy = _strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = build_path(token, command);
		if (is_executable_command(full_path))
			return (free(path_copy), full_path);
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
