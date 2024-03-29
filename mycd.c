#include "main.h"

/**
 * mycd_dot - Changes to the parent directory
 *
 * @datash: data relevant (environ)
 *
 * Return: void
 */
void mycd_dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	myset_env("OLDPWD", cp_pwd, datash);
	dir = datash->args[1];
	if (_mystrcmp(".", dir) == 0)
	{
		myset_env("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}
	if (_mystrcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	myrev_string(cp_strtok_pwd);
	cp_strtok_pwd = _mystrtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _mystrtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			myrev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		myset_env("PWD", cp_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		myset_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(cp_pwd);
}

/**
 * mycd_to - Changes to a given directory
 * by the user
 *
 * @datash: data relevant (directories)
 * Return: void
 */
void mycd_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datash->args[1];
	if (chdir(dir) == -1)
	{
		myget_error(datash, 2);
		return;
	}

	cp_pwd = _mystrdup(pwd);
	myset_env("OLDPWD", cp_pwd, datash);

	cp_dir = _mystrdup(dir);
	myset_env("PWD", cp_dir, datash);

	free(cp_pwd);
	free(cp_dir);

	datash->status = 0;

	chdir(dir);
}

/**
 * mycd_previous - Changes to the previous directory
 *
 * @datash: data relevant (environ)
 * Return: void
 */
void mycd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _mystrdup(pwd);

	p_oldpwd = _mygetenv("OLDPWD", datash->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _mystrdup(p_oldpwd);

	myset_env("OLDPWD", cp_pwd, datash);

	if (chdir(cp_oldpwd) == -1)
		myset_env("PWD", cp_pwd, datash);
	else
		myset_env("PWD", cp_oldpwd, datash);

	p_pwd = _mygetenv("PWD", datash->_environ);

	write(STDOUT_FILENO, p_pwd, _mystrlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datash->status = 0;

	chdir(p_pwd);
}

/**
 * mycd_to_home - Changes to home directory
 *
 * @datash: data relevant (environ)
 * Return: void
 */
void mycd_to_home(data_shell *datash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _mystrdup(pwd);

	home = _mygetenv("HOME", datash->_environ);

	if (home == NULL)
	{
		myset_env("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		myget_error(datash, 2);
		free(p_pwd);
		return;
	}

	myset_env("OLDPWD", p_pwd, datash);
	myset_env("PWD", home, datash);
	free(p_pwd);
	datash->status = 0;
}
