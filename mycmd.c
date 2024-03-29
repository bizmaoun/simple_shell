#include "main.h"

/**
 * myis_cdir - Checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, else 0.
 */
int myis_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _mywhich - Locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: the location of the command.
 */
char _mywhich(char *cmd, char *_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _mygetenv("PATH", _environ);
	if (path)
	{
		ptr_path = _mystrdup(path);
		len_cmd = _mystrlen(cmd);
		token_path = _mystrtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (myis_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _mystrlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_mystrcpy(dir, token_path);
			_mystrcat(dir, "/");
			_mystrcat(dir, cmd);
			_mystrcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _mystrtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * myis_executable - Determines if is an executable
 *
 * @datash: data structure
 * Return: 0 if is not an executable or another number if it does
 */
int myis_executable(data_shell *datash)
{
	struct stat st;
	int i;
	char *input;

	input = datash->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	myget_error(datash, 127);
	return (-1);
}

/**
 * mycheck_error_cmd - Verifies if a user has permissions to access
 *
 * @dir: destination directory
 * @datash: data structure
 * Return: 1 if there is an error, else 0
 */
int mycheck_error_cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		myget_error(datash, 127);
		return (1);
	}

	if (_mystrcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			myget_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			myget_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * mycmd_exec - Executes the command lines
 *
 * @datash: data relevant (args and input)
 * Return: 1 on success.
 */
int mycmd_exec(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = myis_executable(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _mywhich(datash->args[0], datash->_environ);
		if (mycheck_error_cmd(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _mywhich(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}
