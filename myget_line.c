#include "main.h"

/**
 * mybring_line - Assign a line var for get_line
 * @lineptr: buffers that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 * Return: void
 */
void mybring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_mystrcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * myget_line - Reads input from stream
 * @lineptr: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: Number of bytes
 */
ssize_t myget_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _myrealloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	mybring_line(lineptr, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}
