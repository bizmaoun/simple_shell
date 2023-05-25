#include "main.h"

/**
 * find_cmmnd_path - finds this cmd in the PATH string
 * @info: info struct
 * @pathstr: PATH string
 * @cmd: a cmd to find
 *
 * Return: full path of cmd if found otherwise NULL
 */
char *find_cmmnd_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * is_cmmnd - determines if a file is an executable command
 * @info: info struct
 * @path: a path to the file
 *
 * Return: 1 if true else 0
 */
int is_cmmnd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplica_chars - duplicates characters
 * @pathstr: PATH string
 * @start: the starting index
 * @stop: the stopping index
 *
 * Return: pointer to a new buffer
 */
char *duplica_chars(char *pathstr, int start, int stop)
{
	static xhar buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}
