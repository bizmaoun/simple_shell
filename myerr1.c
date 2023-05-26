#include "main.h"

/**
 * mystrcat_cd - concatenates the message for cd error
 *
 * @datash: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *mystrcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_mystrcpy(error, datash->av[0]);
	_mystrcat(error, ": ");
	_mystrcat(error, ver_str);
	_mystrcat(error, ": ");
	_mystrcat(error, datash->args[0]);
	_mystrcat(error, msg);
	if (datash->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datash->args[1][1];
		illegal_flag[2] = '\0';
		_mystrcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_mystrcat(error, datash->args[1]);
	}

	_mystrcat(error, "\n");
	_mystrcat(error, "\0");
	return (error);
}

/**
 * myerror_get_cd - error message for cd command in get_cd
 * @datash: data relevant (directory)
 * Return: Error message
 */
char *myerror_get_cd(data_shell *datash)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = myaux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _mystrlen(datash->args[1]);
	}

	length = _mystrlen(datash->av[0]) + _mystrlen(datash->args[0]);
	length += _mystrlen(ver_str) + _mystrlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = mystrcat_cd(datash, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * myerror_not_found - error message for command not found
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
char *myerror_not_found(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = myaux_itoa(datash->counter);
	length = _mystrlen(datash->av[0]) + _mystrlen(ver_str);
	length += _mystrlen(datash->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_mystrcpy(error, datash->av[0]);
	_mystrcat(error, ": ");
	_mystrcat(error, ver_str);
	_mystrcat(error, ": ");
	_mystrcat(error, datash->args[0]);
	_mystrcat(error, ": not found\n");
	_mystrcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * myerror_exit_shell - error message for exit in get_exit
 * @datash: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *myerror_exit_shell(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = myaux_itoa(datash->counter);
	length = _mystrlen(datash->av[0]) + _mystrlen(ver_str);
	length += _mystrlen(datash->args[0]) + _mystrlen(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_mystrcpy(error, datash->av[0]);
	_mystrcat(error, ": ");
	_mystrcat(error, ver_str);
	_mystrcat(error, ": ");
	_mystrcat(error, datash->args[0]);
	_mystrcat(error, ": Illegal number: ");
	_mystrcat(error, datash->args[1]);
	_mystrcat(error, "\n\0");
	free(ver_str);

	return (error);
}
