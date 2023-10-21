#include "shell.h"
/**
 * is_chain - check if chain
 * @info: info_t
 * @buffer: buffer
 * @ptr: position in buf
 *
 * Return: 1 if chain, 0 otherwise
 */
int is_chain(info_t *info, char *buffer, size_t *ptr)
{
	size_t i = *ptr;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		info->cmd_buffer_type = CMD_OR;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		info->cmd_buffer_type = CMD_AND;
	}
	else if (buffer[i] == ';')
	{
		buffer[i] = 0;
		info->cmd_buffer_type = CMD_SEPAR;
	}
	else
		return (0);
	*ptr = i;

	return (1);
}
/**
 * check_chain - checks if continue chain based on last status
 * @info: info_t
 * @buffer: buffer
 * @ptr: position in buffer
 * @p_s: starting pos
 * @len: buffer length
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buffer,
		size_t *ptr, size_t p_s, size_t len)
{
	size_t j = *ptr;

	if (info->cmd_buffer_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[p_s] = 0;
			j = len;
		}
	}
	if (info->cmd_buffer_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[p_s] = 0;
			j = len;
		}
	}
	*ptr = j;
}
/**
 * alias_replace - replaces alias
 * @info: info_t
 * Return: 1 if replaced, 0 otherwise
 */
int alias_replace(info_t *info)
{
	list_t *node;
	int i;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = node_start_prefix(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);

		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}
/**
 * vars_replace - replace var
 * @info: info_t
 *
 * Return: 1 if replaced, 0 otherwise
 */
int vars_replace(info_t *info)
{
	list_t *node;
	int i = 0;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_str(&(info->argv[i]),
				_strdup(convert_num(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_str(&(info->argv[i]),
				_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = node_start_prefix(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_str(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_str(&info->argv[i], _strdup(""));

	}
	return (0);
}
/**
 * replace_str - replaces
 * @oldstr: old str
 * @newstr: new str
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_str(char **oldstr, char *newstr)
{
	free(*oldstr);
	*oldstr = newstr;
	return (1);
}
