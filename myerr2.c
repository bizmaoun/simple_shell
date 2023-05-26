#include "main.h"

/**
 * myerror_env - show error message for env in get_env.
 * @datash: data relevant (counter, arguments)
 * Return: error message.
 */
char *myerror_env(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = myaux_itoa(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _mystrlen(datash->av[0]) + _mystrlen(ver_str);
	length += _mystrlen(datash->args[0]) + _mystrlen(msg) + 4;
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
	_mystrcat(error, msg);
	_mystrcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * myerror_path_126 - show error message for path and failure denied permission.
 * @datash: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *myerror_path_126(data_shell *datash)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = myaux_itoa(datash->counter);
	length = _mystrlen(datash->av[0]) + _mystrlen(ver_str);
	length += _mystrlen(datash->args[0]) + 24;
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
	_mystrcat(error, ": Permission denied\n");
	_mystrcat(error, "\0");
	free(ver_str);
	return (error);
}
