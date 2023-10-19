#include "shell.h"
/**
 * print_env - prints env built-in
 *
 * Return: void
 */
void print_env(void)
{
	extern char **environ;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		out_print(environ[i]);
		out_print("\n");
	}
}
