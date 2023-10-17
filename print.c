#include "shell.h"
/**
 * out_print - prints a message to stdout
 * @msg: the message
 *
 * Return: void
 */
void out_print(const char *msg)
{
	write(STDOUT_FILENO, msg, strlen(msg));
}
