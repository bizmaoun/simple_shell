#include "main.h"

/**
 * myexit_shell - Quit the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int myexit_shell(data_shell *datash)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (datash->args[1] != NULL)
	{
		ustatus = _myatoi(datash->args[1]);
		is_digit = _myisdigit(datash->args[1]);
		str_len = _mystrlen(datash->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			myget_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (ustatus % 256);
	}
	return (0);
}
