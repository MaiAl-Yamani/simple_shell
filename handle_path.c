#include "shell.h"
/**
 * is_command - check if a command is executable
 * @info: info_t struct
 * @file_path: path
 *
 * Return: 1 if true, 0 otherwise
 */
int is_command(info_t *info, char *file_path)
{
	struct stat st;

	(void)info;
	if (!file_path || stat(file_path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * dup_ch - duplicates chars
 * @path_str: PATH string
 * @start_idx: start index
 * @stop_idx: stop index
 *
 * Return: pointer to new buf
 */
char *dup_ch(char *path_str, int start_idx, int stop_idx)
{
	static char buffer[1024];
	int i = 0, j = 0;

	for (j = 0, i = start_idx; i < stop_idx; i++)
		if (path_str[i] != ':')
			buffer[j++] = path_str[i];
	buffer[j] = 0;
	return (buffer);
}
/**
 * find_path - finds this cmd input in PATH
 * @info: info_t struct
 * @path_str: PATH
 * @command: command input
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *path_str, char *command)
{
	int i = 0, curr_position = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((_strlen(command) > 2) && start_with(command, "./"))
	{
		if (is_command(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = dup_ch(path_str, curr_position, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_command(info, path))
				return (path);
			if (!path_str[i])
				break;
			curr_position = i;
		}
		i++;
	}

	return (NULL);
}
