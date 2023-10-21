#include "shell.h"
/**
 * _hsh_env - prints env
 * @info: info_t structure
 *
 * Return: Always 0
 */
int _hsh_env(info_t *info)
{
	print_str_list(info->env);
	return (0);
}
/**
 * _getenv - gets the value of an environ
 * @info: info_t structure
 * @env_name: env var name
 *
 * Return: value of environ
 */
char *_getenv(info_t *info, const char *env_name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = start_with(node->str, env_name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}
/**
 * _hsh_setenv - Initialize new env variable, or modify an existing env
 * @info: info_t struct
 *
 *  Return: Always 0
 */
int _hsh_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_errputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/**
 * _hsh_unsetenv - Remove an env variable
 * @info: info_t struct
 *
 *  Return: Always 0
 */
int _hsh_unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_errputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_ll - populates env linked list
 * @info: info_t struct
 *
 * Return: Always 0
 */
int populate_env_ll(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
