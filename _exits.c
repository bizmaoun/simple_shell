#include "main.h"

/**
 * *_lochar - locates a character ina  string
 * @s: string to be parsed
 * @c: character to look for
 * Return: (s) a pointer to the memory area s
 */
char *_lochar(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * *_cpynstr - copies a string
 * @dest: destination string to be copied to
 * @src: source string
 * @n: amount of characters to be copied
 * Return: a concatenated string
 */
char *_cpynstr(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest(j) = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * *_catnstr - concatenates two strings
 * @dest: first or destination string
 * @src: second or source string
 * @n: amount of bytes to be maximally used
 * Return: a concanated string
 */
char *_catnstr(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}
