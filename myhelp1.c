#include "main.h"

/**
 * myaux_help_env - Give help information for the builtin env
 * Return: void
 */
void myaux_help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, _mystrlen(help));

}
/**
 * myaux_help_setenv - Provides help information for the builtin setenv
 * Return: void
 */
void myaux_help_setenv(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _mystrlen(help));
}
/**
 * myaux_help_unsetenv - Gives help information for the builtin unsetenv
 * Return: void
 */
void myaux_help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, _mystrlen(help));
}


/**
 * myaux_help_general - The entry point for help information for the help builtin
 * Return: void
 */
void myaux_help_general(void)
{
	char *help = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, _mystrlen(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, _mystrlen(help));
}
/**
 * myaux_help_exit - The help information fot the builint exit
 * Return: void
 */
void myaux_help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, _mystrlen(help));
	help = "status that of the last command executed\n";
	write(STDOUT_FILENO, help, _mystrlen(help));
}
