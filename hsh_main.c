#include "shell.h"
/**
 * hsh_func - main shell
 * @info: info_t struct
 * @argv: arguments array
 *
 * Return: 0 on success, 1 on error, or return an error code
 */
int hsh_func(info_t *info, char **argv)
{
	ssize_t r = 0;
	int builtin_return = 0;

	while (r != -1 && builtin_return != -2)
	{
		clear_info_struct(info);
		if (is_interactive(info))
			_puts("$ ");
		_err_putchar(BUF_FLUSH);
		r = get_input_line(info);
		if (r != -1)
		{
			set_info_struct(info, argv);
			builtin_return = find_builtin(info);
			if (builtin_return == -1)
				find_command(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		free_info_struct(info, 0);
	}
	write_hist(info);
	free_info_struct(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_return == -2)
	{
		if (info->err_n == -1)
			exit(info->status);
		exit(info->err_n);
	}
	return (builtin_return);
}
/**
 * find_builtin - finds builtin command
 * @info: info_t struct
 *
 * Return: -1 if builtin not found, 0 if executed successfully,
 *			1 if not successful, -2 if signals exit()
 */
int find_builtin(info_t *info)
{
	int i, builtin_return = -1;
	builtin_t builtin_tbl[] = {
		{"exit", _hsh_exit},
		{"env", _hsh_env},
		{"help", _hsh_help},
		{"history", _hsh_history},
		{"setenv", _hsh_setenv},
		{"unsetenv", _hsh_unsetenv},
		{"cd", _hsh_cd},
		{"alias", _hsh_alias},
		{NULL, NULL}
	};

	for (i = 0; builtin_tbl[i].type; i++)
		if (_strcmp(info->argv[0], builtin_tbl[i].type) == 0)
		{
			info->line_cnt++;
			builtin_return = builtin_tbl[i].func(info);
			break;
		}
	return (builtin_return);
}
/**
 * find_command - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_command(info_t *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecnt_flag == 1)
	{
		info->line_cnt++;
		info->linecnt_flag = 0;
	}

	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((is_interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_err(info, "not found\n");
		}
	}
}
/**
 * fork_command - fork and exec stage
 * @info: info_t struct
 *
 * Return: void
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info_struct(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_err(info, "Permission denied\n");
		}
	}
}
