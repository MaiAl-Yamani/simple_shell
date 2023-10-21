#include "shell.h"
/**
 * _putchar - prints the char c to stdout
 * @ch: The char to print
 *
 * Return: On success 1, on error -1 and errno is set appropriately.
 */
int _putchar(char ch)
{
	static int i;
	static char buffer[WR_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WR_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[i++] = ch;
	return (1);
}
/**
 *_puts - prints a string
 *@str: string to be printed
 *
 * Return: void
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
/**
 * start_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *start_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * _strcpy - copy a string
 * @dest: string
 * @src: string
 *
 * Return: dest string pointer
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
