#include "main.h"

/**
 * myrepeated_char - Counts the repetitions of a character
 *
 * @input: input string
 * @i: index
 * Return: the repetitions
 */
int myrepeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (myrepeated_char(input - 1, i + 1));

	return (i);
}

/**
 * myerror_sep_op - Looks for syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when no errors
 */
int myerror_sep_op(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (myerror_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = myrepeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = myrepeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (myerror_sep_op(input + 1, i + 1, *input));
}

/**
 * myfirst_char - Gets the index of the first character
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error, else 0.
 */
int myfirst_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * myprint_syntax_error - Prints when a syntax error is found
 *
 * @datash: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: void
 */
void myprint_syntax_error(data_shell *datash, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = myaux_itoa(datash->counter);
	length = _mystrlen(datash->av[0]) + _mystrlen(counter);
	length += _mystrlen(msg) + _mystrlen(msg2) + _mystrlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_mystrcpy(error, datash->av[0]);
	_mystrcat(error, ": ");
	_mystrcat(error, counter);
	_mystrcat(error, msg2);
	_mystrcat(error, msg);
	_mystrcat(error, msg3);
	_mystrcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * mycheck_syntax_error - Finds and prints a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error, else 0
 */
int mycheck_syntax_error(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = myfirst_char(input, &begin);
	if (f_char == -1)
	{
		myprint_syntax_error(datash, input, begin, 0);
		return (1);
	}

	i = myerror_sep_op(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		myprint_syntax_error(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}
