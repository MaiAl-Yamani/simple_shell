#include "shell.h"
/**
 * listlen - returns linked list length
 * @head: pointer to head of linked list
 *
 * Return: list size
 */
size_t listlen(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}
/**
 * list_to_str - returns array of strings of the list->str
 * @h: pointer to head
 *
 * Return: array of strings
 */
char **list_to_str(list_t *h)
{
	list_t *node = h;
	size_t i = listlen(h), j;
	char **strings;
	char *str;

	if (!h || !i)
		return (NULL);
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strings[i] = str;
	}
	strings[i] = NULL;
	return (strings);
}
/**
 * print_ll - prints elements of a list_t ll
 * @head: pointer to head
 *
 * Return: list size
 */
size_t print_ll(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(convert_num(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}
/**
 * node_start_prefix - returns node whose string starts with prefix
 * @node: list_t pointer
 * @prefix: prefix to match with
 * @ch: the next character after prefix to match
 *
 * Return: matching node or null
 */
list_t *node_start_prefix(list_t *node, char *prefix, char ch)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = start_with(node->str, prefix);
		if (ptr && ((ch == -1) || (*ptr == ch)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * get_node_idx - gets index of a node
 * @h: pointer to list head
 * @node: pointer to the node
 *
 * Return: idx of node or -1
 */
ssize_t get_node_idx(list_t *h, list_t *node)
{
	size_t i = 0;

	while (h)
	{
		if (h == node)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}
