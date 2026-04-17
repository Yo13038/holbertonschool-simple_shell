#include "main.h"
/**
 * _getenv - Searches the environment list to find a specific variable.
 * @name: The name of the environment variable to find (e.g., "PATH").
 *
 * Return: A pointer to the value string after the '=' sign,
 * or NULL if the variable is not found.
 */
char *_getenv(const char *name)
{
	int i = 0;
	int len = _strlen((char *)name);

	/* Check for NULL inputs or empty environment */
	if (environ == NULL || name == NULL)
		return (NULL);
	
	/* Go through the environment until the end (NULL) */
	while (environ[i] != NULL)
	{
		/* Compare the variable name and check for the '=' character */
		if (_strncmp(environ[i], (char *)name, len) == 0 && environ[i][len] == '=')
		{
			/* Return the address starting right after the '=' */
			return (environ[i] + len + 1);
		}
		i++;
	}
	/* If no match is found, return NULL */
	return (NULL);
}
/**
 * contains_slash - Checks if the given command contains a directory path.
 * @command: The string to be scanned.
 *
 * Return: 1 if a slash is found, 0 otherwise.
 */
int contains_slash(char *command)
{
	int i = 0;

	/* If the string is empty, it can't contain a slash */
	if (command == NULL)
		return (0);

	/* Go through the string until the null terminator */
	while (command[i] != '\0')
	{
		/* If character is a '/', return success (1) */
		if (command[i] == '/')
		{
			return (1);
		}
		i++;
	}
	/* No slash found after scanning the entire string */
	return (0);
}
/**
 * build_path - Combines a directory path and a command name into a full path.
 * @dir: The directory (e.g., "/bin").
 * @cmd: The command name (e.g., "ls").
 *
 * Return: allocated string containing the full path, or NULL on failure.
 */
char *build_path(char *dir, char *cmd)
{
	char *path;
	int len_dir, len_cmd;

	if (dir == NULL || cmd == NULL)
		return (NULL);

	len_dir = _strlen(dir);
	len_cmd = _strlen(cmd);

	/* Allocate memory */
	path = malloc(sizeof(char) * (len_dir + len_cmd + 2));
	
	if (path == NULL)
		return (NULL);

	/* Build the string */
	_strcpy(path, dir);     /* Copy directory */
	path[len_dir] = '/';    /* Add slash at the end of directory */
	_strcpy(path + len_dir + 1, cmd); /* Copy command right after '/' */

	return (path);
}

/**
 * is_executable_command - Checks if a file exists and is accessible.
 * @path: The full path to the file to check.
 *
 * Return: 1 if the file is found, 0 otherwise.
 */
int is_executable_command(char *path)
{
	struct stat st;

	/* Check if the path is valid and if stat can find the file */
	if (path != NULL && stat(path, &st) == 0)
	{
		return (1);
	}
	return (0);
}

/**
 * find_command - Locates an executable command within the PATH directories.
 * @command: The name of the command (e.g., "ls").
 *
 * Return: A newly allocated string containing the full path, 
 * or NULL if the command is not found.
 */
char *find_command(char *command)
{
	char *path_env, *path_copy, *token, *full_path;

	if (command == NULL)
		return (NULL);

	/* Handle cases where command is already a full or relative path */
	if (contains_slash(command))
	{
		if (is_executable_command(command))
			return (_strdup(command)); /* Return a copy to be freed later */
		return (NULL);
	}

	/* Get the content of the PATH environment variable */
	path_env = _getenv("PATH");
	if (!path_env)
		return (NULL);

	/* Duplicate PATH because strtok modifies the string */
	path_copy = _strdup(path_env);
	if (!path_copy)
		return (NULL);

	/* Split PATH into directory tokens and test them */
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		/* Create the potential full path */
		full_path = build_path(token, command);

		if (is_executable_command(full_path))
		{
			free(path_copy); /* Freework copy */
			return (full_path); /* Success! Return the allocated path */
		}

		/* If not found, free the failed path and move to next token */
		free(full_path);
		token = strtok(NULL, ":");
	}

	/* free and return NULL if command is not to be found */
	free(path_copy);
	return (NULL);
}