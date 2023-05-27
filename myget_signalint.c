#include "main.h"

/**
 * get_sigint - Handles the control + c call in prompt
 * @sig: Signal handler
 */
void myget_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
