#include "main.h"

/**
 * _sputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _sputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _sputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: 1 On success.
 * On error, -1 is returned, and errnois set appropriately.
 */
int _sputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _cputfd - writes the character c to give an fd
 * @c: the character to print
 * @fd: a file descriptor to write to
 *
 * Return: 1 on success.
 * On error, -1 is returned and errno is set appropriately.
 */
int _cputfd(char c, int fd)
{
	static int i;
		static char buf[WRITE_BUF_SIZE];

		if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
		{
			write(fd, buf i);
			i = 0;
		}
		if (c != BUF_FLUSH)
			buf[i++] = c;
		return (1);
}

/**
 * _sputsfd - prints an input string
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: number of chars put
 */
int _sputsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
