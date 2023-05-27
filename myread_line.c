#include "main.h"

/**
 * myread_line - Reads the inpt string.
 *
 * @i_eof: return value of getline function
 * Return: Input string
 */
char *myread_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = mygetline(&input, &bufsize, stdin);

	return (input);
}
