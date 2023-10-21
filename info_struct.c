#include "shell.h"
/**
 * clear_info_struct - clears info_t struct
 * @info: info_t struct
 *
 * Return: void
 */
void clear_info_struct(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * set_info_struct - initializes
 * @info: info_t struct
 * @argv: argument values
 */
void set_info_struct(info_t *info, char **argv)
{
	int i = 0;

	info->filename = argv[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		alias_replace(info);
		vars_replace(info);
	}
}
/**
 * free_info_struct - frees info_t struct (all)
 * @info: info_t struct
 * @all: true if free is succesful for all fields
 *
 * Return: void
 */
void free_info_struct(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buffer)
			free(info->arg);
		if (info->env)
			free_str_list(&(info->env));
		if (info->hist)
			free_str_list(&(info->hist));
		if (info->alias)
			free_str_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buffer);
		if (info->rd_fd > 2)
			close(info->rd_fd);
		_putchar(BUF_FLUSH);
	}
}
