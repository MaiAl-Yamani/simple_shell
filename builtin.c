#include "shell.h"
/**
 * _hsh_exit - exits
 * @info: info_t
 *
 * Return: exits with status
 */
int _hsh_exit(info_t *info)
{
	int exit_check;

	if (info->argv[1])
	{
		exit_check = _err_atoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_err(info, "Illegal number: ");
			_errputs(info->argv[1]);
			_err_putchar('\n');
			return (1);
		}
		info->err_n = _err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_n = -1;
	return (-2);
}
/**
 * _hsh_cd - changes dir
 * @info: info_t
 *
 * Return: Always 0
 */
int _hsh_cd(info_t *info)
{
	char *str, *dirrec, buf[1024];
	int chdir_return;

	str = getcwd(buf, 1024);
	if (!str)
		_puts("getcwd failure\n");
	if (!info->argv[1])
	{
		dirrec = _getenv(info, "HOME=");
		if (!dirrec)
			chdir_return = chdir((dirrec = _getenv(info, "PWD=")) ? dirrec : "/");
		else
			chdir_return = chdir(dirrec);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_return = chdir((dirrec = _getenv(info, "OLDPWD=")) ? dirrec : "/");
	}
	else
		chdir_return = chdir(info->argv[1]);
	if (chdir_return == -1)
	{
		print_err(info, "can't cd to ");
		_errputs(info->argv[1]), _err_putchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buf, 1024));
	}

	return (0);
}
/**
 * _hsh_help - help command handling
 * @info: info_t
 *
 * Return: Always 0
 */
int _hsh_help(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works.\n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
