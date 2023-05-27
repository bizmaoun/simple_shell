#include "main.h"

/**
 * myexec_line - Finds commands and builtins
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int myexec_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = myget_builtin(datash->args[0]);

	if (builtin != NULL)
		return (mybuiltin(datash));

	return (mycmd_exec(datash));
}
