#include "main.h"

/**
 * myget_error - calls the error according to the builtin, permission or syntax
 * @datash: data structure that contains arguments
 * @eval: err value
 * Return: error
 */
int myget_error(data_shell *datash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = myerror_env(datash);
		break;
	case 126:
		error = myerror_path_126(datash);
		break;
	case 127:
		error = myerror_not_found(datash);
		break;
	case 2:
		if (_mystrcmp("exit", datash->args[0]) == 0)
			error = myerror_exit_shell(datash);
		else if (_mystrcmp("cd", datash->args[0]) == 0)
			error = myerror_get_cd(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _mystrlen(error));
		free(error);
	}

	datash->status = eval;
	return (eval);
}
