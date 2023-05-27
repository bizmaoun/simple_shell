#include "main.h"

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	myset_data(&datash, av);
	myshell_loop(&datash);
	myfree_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}

/**
 * myfree_data - Frees the data structure
 *
 * @datash: data structure
 * Return: void
 */
void myfree_data(data_shell *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * myset_data - Initialize data structure
 *
 * @datash: data structure
 * @av: argument vector
 * Return: void
 */
void myset_data(data_shell *datash, char **av)
{
	unsigned int i;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	datash->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = _mystrdup(environ[i]);
	}

	datash->_environ[i] = NULL;
	datash->pid = myaux_itoa(getpid());
}
