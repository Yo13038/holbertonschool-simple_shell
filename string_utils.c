#include "main.h"

/**
 * _strlen - computes the length of a string
 * @s: string to measure
 *
 * Return: number of characters in the string
 */
int _strlen(char *s)
{
	int len;

	if (s == NULL)
		return (0);

	len = 0;
	while (s[len] != '\0')
		len++;

	return (len);
}

/**
 * _strcpy - copies a string into a destination buffer
 * @dest: destination buffer
 * @src: source string
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	if (dest == NULL || src == NULL)
		return (dest);

	i = 0;
	while (src[i] != '\0')
	{
		/* Copy one character at a time */
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * _strdup - duplicates a string in newly allocated memory
 * @s: string to duplicate
 *
 * Return: pointer to the duplicated string, or NULL on failure
 */
char *_strdup(char *s)
{
	char *new_str;
	int len;

	if (s == NULL)
		return (NULL);

	len = _strlen(s);
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);

	/* Copy the original string into the new allocated buffer */
	_strcpy(new_str, s);
	return (new_str);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if equal, difference otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		/* Stop as soon as a different character is found */
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (s1[i] - s2[i]);
}

/**
 * _strncmp - compares two strings up to n characters
 * @s1: first string
 * @s2: second string
 * @n: maximum number of characters to compare
 *
 * Return: 0 if equal up to n, difference otherwise
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		/* Return the difference at the first mismatch */
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i == n)
		return (0);

	return (s1[i] - s2[i]);
}
