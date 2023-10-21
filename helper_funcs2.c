#include "shell.h"
/**
 * _err_ator - converts a string to an integer
 * @str: string input
 * Return: 0 if no numbers in str, or converted number, -1 on error
 */
int _err_atoi(char *str)
{
	int i = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;  /* 255? */
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res *= 10;
			res += (str[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}
/**
 * print_err - prints error message
 * @info: info_t struct
 * @estr_type: string with error type
 * Return: 0 if no numbers in str, or converted number, -1 on error
 */
void print_err(info_t *info, char *estr_type)
{
	_errputs(info->filename);
	_errputs(": ");
	print_dec(info->line_cnt, STDERR_FILENO);
	_errputs(": ");
	_errputs(info->argv[0]);
	_errputs(": ");
	_errputs(estr_type);
}
/**
 * print_dec - prints a decimal num
 * @in: int input
 * @fd: file descriptor to write to
 *
 * Return: number of chars printed
 */
int print_dec(int in, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, cnt = 0;
	unsigned int _abs_, crnt;

	if (fd == STDERR_FILENO)
		__putchar = _err_putchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		cnt++;
	}
	else
		_abs_ = in;
	crnt = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + crnt / i);
			cnt++;
		}
		crnt %= i;
	}
	__putchar('0' + crnt);
	cnt++;
	return (cnt);
}
/**
 * convert_num - converter
 * @number: int
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_num(long int number, int base, int flags)
{
	static char *arr;
	static char buf[50];
	char sign = 0;
	char *p;
	unsigned long n = number;

	if (!(flags & CONVERT_UNSIGN) && number < 0)
	{
		n = -number;
		sign = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';

	do	{
		*--p = arr[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--p = sign;
	return (p);
}
/**
 * rm_comments - replace first instance of '#' with '\0'
 * @buffer: string to be modified address
 *
 * Return: Always 0;
 */
void rm_comments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}
