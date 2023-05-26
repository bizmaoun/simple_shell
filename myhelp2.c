#include "main.h"

/**
 * myaux_help - The help information for the builtin help.
 * Return: void
 */
void myaux_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _mystrlen(help));
}

/**
 * myaux_help_alias - The help information for the builtin alias.
 * Return: void
 */
void myaux_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _mystrlen(help));
}

/**
 * myaux_help_cd - The help information for the builtin alias.
 * Return: void
 */
void myaux_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _mystrlen(help));
}
