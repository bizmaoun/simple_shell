#include "main.h"

/**
 * mycmp_env_name - Compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: the passed name
 *
 * Return: 0 if are not equal or another value if they are.
 */
int mycmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _mygetenv - Gets an environment variable
 * @name: name of the environment variable
 * @_environ: the environment variable
 *
 * Return: value of the environment variable if is found else returns NULL.
 */
char *_mygetenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;
	ptr_env = NULL;
	mov = 0;

	for (i = 0; _environ[i]; i++)
	{
		mov = mycmp_env_name(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _myenv - Prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _myenv(data_shell *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{

		for (j = 0; datash->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
