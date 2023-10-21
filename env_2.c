#include "shell.h"
/**
 * get_environ - returns array copy of our environ
 * @info: info_t struct
 *
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_change)
	{
		info->environ = list_to_str(info->env);
		info->env_change = 0;
	}
	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: info_t struct
 * @var: env var property
 *
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node_ll = info->env;
	size_t i = 0;
	char *ptr;

	if (!node_ll || !var)
		return (0);
	while (node_ll)
	{
		ptr = start_with(node_ll->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_change = delete_node_at_idx(&(info->env), i);
			i = 0;
			node_ll = info->env;
			continue;
		}
		node_ll = node_ll->next;
		i++;
	}
	return (info->env_change);
}
/**
 * _setenv - Initialize new env variable, orr modify an existing env
 * @info: info_t struct
 * @var: env var property
 * @val: value of env var
 *
 * Return: Always 0
 */
int _setenv(info_t *info, char *var, char *val)
{
	char *buffer = NULL;
	list_t *node_ll;
	char *ptr;

	if (!var || !val)
		return (0);
	buffer = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, val);
	node_ll = info->env;

	while (node_ll)
	{
		ptr = start_with(node_ll->str, var);
		if (ptr && *ptr == '=')
		{
			free(node_ll->str);
			node_ll->str = buffer;
			info->env_change = 1;
			return (0);
		}
		node_ll = node_ll->next;
	}

	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_change = 1;
	return (0);
}
