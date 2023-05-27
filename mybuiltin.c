#include "main.h"

/**
 * myget_builtin - Built in that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the built in command
 */
int (*myget_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_mystrcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}
