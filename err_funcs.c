#include "shell.h"
/**
 *_errputs - prints a string
 * @s: to be printed
 *
 * Return: void
 */
void _errputs(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_err_putchar(s[i]);
		i++;
	}
}
/**
 * _err_putchar - displays char to stderr
 * @ch: char
 *
 * Return: On success 1, on error -1, errno is set appropriately.
 */
int _err_putchar(char ch)
{
	static int i;
	static char buffer[WR_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WR_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[i++] = ch;
	return (1);
}
/**
 * _putfd - writes c char to specific fd
 * @ch: char
 * @fd: file descriptor
 *
 * Return: 1 on success -1 on error and errno is set appropriately.
 */
int _putfd(char ch, int fd)
{
	static int i;
	static char buffer[WR_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WR_BUF_SIZE)
	{
		write(fd, buffer, i);
		i = 0;
	}

	if (ch != BUF_FLUSH)
		buffer[i++] = ch;
	return (1);
}
/**
 *_putsfd - prints input string
 * @s: string input
 * @fd: file descriptor that the func writes to
 *
 * Return: number of chars printed
 */
int _putsfd(char *s, int fd)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += _putfd(*s++, fd);
	}
	return (i);
}
