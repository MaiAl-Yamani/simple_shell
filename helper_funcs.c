#include "shell.h"
/**
 * is_interactive - checks if in interactive mode
 * @info: info_t struct
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->rd_fd <= 2);
}
/**
 * is_delim_ch - checks if ch is a delimeter
 * @ch: char
 * @delimeter: delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char ch, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == ch)
			return (1);
	return (0);
}
/**
 * _isalpha - checks if alphabetic char
 * @ch: char
 *
 * Return: 1 if ch is alphabetic, 0 otherwise
 */
int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - converts a str to an int
 * @str: string input
 *
 * Return: 0 if no numbers in str, converted number otherwise
 */
int _atoi(char *str)
{
	int i, sign = 1, flag = 0, out;
	unsigned int res = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		out = -res;
	else
		out = res;

	return (out);
}
