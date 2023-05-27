#include "main.h"

/**
 * myget_help - Retrieves help messages according to built in
 * @datash: data structure (args and input)
 * Return: 0
*/
int myget_help(data_shell *datash)
{

	if (datash->args[1] == 0)
		myaux_help_general();
	else if (_mystrcmp(datash->args[1], "setenv") == 0)
		myaux_help_setenv();
	else if (_mystrcmp(datash->args[1], "env") == 0)
		aux_help_env();
	else if (_mystrcmp(datash->args[1], "unsetenv") == 0)
		myaux_help_unsetenv();
	else if (_mystrcmp(datash->args[1], "help") == 0)
		myaux_help();
	else if (_mystrcmp(datash->args[1], "exit") == 0)
		myaux_help_exit();
	else if (_mystrcmp(datash->args[1], "cd") == 0)
		myaux_help_cd();
	else if (_mystrcmp(datash->args[1], "alias") == 0)
		myaux_help_alias();
	else
		write(STDERR_FILENO, datash->args[0],
		      _mystrlen(datash->args[0]));

	datash->status = 0;
	return (1);
}
