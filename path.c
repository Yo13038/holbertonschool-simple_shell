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
 * find_command - Finds the full path of a given command.
 * @command: The command to locate (e.g., "ls").
 *
 * Return: A pointer to the full path string, or NULL if not found.
 */
char *find_command(char *command)
{
	char *path_env, *path_copy, *token, *full_path;
	struct stat st;

	/* Handle direct paths (e.g., /bin/ls */
	if (contains_slash(command))
	{
		if (stat(command, &st) == 0)
			return (_strdup(command));
		else
			return (NULL);
	}
	
	/* Retrieve the PATH */
	path_env = _getenv("PATH");
	if (!path_env || _strlen(path_env) == 0)
		return (NULL);

	/* Copy PATH to tokenize it */
	path_copy = _strdup(path_env);
	if (!path_copy)
		return (NULL);

	/*Loop through directories in PATH */
	token = strtok(path_copy, ":");
	
	while (token != NULL)
	{
		full_path = build_path(token, command);
		
		if (stat(full_path, &st) == 0)
		{
			free(path_copy); /* Clean up the copy */
			return (full_path); /* Found the executable! */
		}
		
		free(full_path); /* Not found, free and try next directory */
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL); /* Command was not found in PATH */
}
