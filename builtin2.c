#include "shell.h"
/**
 * _hsh_history - displays the history list
 * @info: info_t
 *
 * Return: Always 0
 */
int _hsh_history(info_t *info)
{
	print_str_list(info->hist);
	return (0);
}
/**
 * alias_unset - sets alias to str
 * @info: info_t
 * @str: string
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_unset(info_t *info, char *str)
{
	char *ptr, c;
	int res;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	res = delete_node_at_idx(&(info->alias),
		get_node_idx(info->alias, node_start_prefix(info->alias, str, -1)));

	*ptr = c;
	return (res);
}
/**
 * alias_set - sets alias
 * @info: parameter struct
 * @str: string
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_set(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (alias_unset(info, str));
	alias_unset(info, str);

	return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * alias_print - prints alias
 * @node_in: node
 *
 * Return: Always 0 if success, 1 if error
 */
int alias_print(list_t *node_in)
{
	char *ptr = NULL, *ar = NULL;

	if (node_in)
	{
		ptr = _strchr(node_in->str, '=');
		for (ar = node_in->str; ar <= ptr; ar++)
			_putchar(*ar);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _hsh_alias - handle alias builtin
 * @info: info_t
 *
 * Return: Always 0
 */
int _hsh_alias(info_t *info)
{
	char *ptr = NULL;
	int i = 0;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			alias_print(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		ptr = _strchr(info->argv[i], '=');
		if (ptr)
			alias_set(info, info->argv[i]);
		else
			alias_print(node_start_prefix(info->alias, info->argv[i], '='));
	}
	return (0);
}
