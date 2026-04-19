#include "main.h"

/**
 * _strlen - Computes the length of a string.
 * @s: The string to measure.
 *
 * Return: The number of characters before the null terminator.
 */
int _strlen(char *s)
{
	int len = 0;

	if (s == NULL)
		return (0);

	while (s[len] != '\0')
		len++;

	return (len);
}

/**
 * _strcpy - Copies the string pointed to by src to dest.
 * @dest: The destination buffer.
 * @src: The source string.
 *
 * Return: The pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == NULL || src == NULL)
		return (dest);

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0'; /* Don't forget the null terminator! */
	return (dest);
}

/**
 * _strdup - Duplicates a string by allocating new memory.
 * @s: The string to duplicate.
 *
 * Return: A pointer to the newly allocated string, or NULL if it fails.
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

	_strcpy(new_str, s);
	return (new_str);
}

/**
 * _strcmp - Compares two strings character by character.
 * @s1: First string.
 * @s2: Second string.
 *
 * Return: 0 if strings are identical, the difference otherwise.
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

/**
 * _strncmp - Compares two strings up to n characters.
 * @s1: First string.
 * @s2: Second string.
 * @n: Maximum number of characters to compare.
 *
 * Return: 0 if match, the difference otherwise.
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i = 0;

	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}