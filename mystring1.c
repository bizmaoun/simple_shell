#include "main.h"

/**
 * _mystrdup - Duplicates a string in the heap memory.
 * @s: Type char pointer str
 * Return: duplicated string
 */
char *_mystrdup(const char *s)
{
	char *new;
	size_t len;

	len = _mystrlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_mymemcpy(new, s, len + 1);
	return (new);
}

/**
 * _mystrlen - Returns lenght of the string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int _mystrlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * mycmp_chars - Compares characters of strings
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: 1 if are equals, else 0.
 */
int mycmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _mystrtok - Splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *_mystrtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (mycmp_chars(str, delim))
			return (NULL);
		splitted = str;
		i = _mystrlen(str);
		str_end = &str[i];
	}
	str_start = splitted;
	if (str_start == str_end)
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_start);
}

/**
 * _myisdigit - Detects if the string passed is a number
 *
 * @s: input string
 * Return: 1 if string is a number, else 0.
 */
int _myisdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
