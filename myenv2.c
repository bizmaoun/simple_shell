#include "main.h"

/**
 * mycopy_info - Copies info to create
 * a new envir or alias
 * @name: name (envir or alias)
 * @value: value (envir or alias)
 *
 * Return: new envir or alias.
 */
char *mycopy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _mystrlen(name);
	len_value = _mystrlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_mystrcpy(new, name);
	_mystrcat(new, "=");
	_mystrcat(new, value);
	_mystrcat(new, "\0");

	return (new);
}

/**
 * myset_env - Sets the environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: void
 */
void myset_env(char *name, char *value, data_shell *datash)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; datash->_environ[i]; i++)
	{
		var_env = _mystrdup(datash->_environ[i]);
		name_env = _mystrtok(var_env, "=");
		if (_mystrcmp(name_env, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = mycopy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _myreallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
	datash->_environ[i] = mycopy_info(name, value);
	datash->_environ[i + 1] = NULL;
}

/**
 * _mysetenv - It compares env vars names with passed name.
 * @datash: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _mysetenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		myget_error(datash, -1);
		return (1);
	}

	myset_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _myunsetenv - Deletes an env variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _myunsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (datash->args[1] == NULL)
	{
		myget_error(datash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datash->_environ[i]; i++)
	{
		var_env = _mystrdup(datash->_environ[i]);
		name_env = _mystrtok(var_env, "=");
		if (_mystrcmp(name_env, datash->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		myget_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = datash->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
