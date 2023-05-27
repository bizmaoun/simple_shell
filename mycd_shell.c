#include "main.h"

/**
 * mycd_shell - Changes the current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int mycd_shell(data_shell *datash)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		ishome = _mystrcmp("$HOME", dir);
		ishome2 = _mystrcmp("~", dir);
		isddash = _mystrcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		mycd_to_home(datash);
		return (1);
	}

	if (_mystrcmp("-", dir) == 0)
	{
		mycd_previous(datash);
		return (1);
	}

	if (_mystrcmp(".", dir) == 0 || _mystrcmp("..", dir) == 0)
	{
		mycd_dot(datash);
		return (1);
	}

	mycd_to(datash);

	return (1);
}
