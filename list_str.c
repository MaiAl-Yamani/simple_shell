#include "shell.h"
/**
 * add_node - adds node to list
 * @head: pointer to pointer to head
 * @str: str argumnet of node
 * @num: index of node used by hist
 *
 * Return: list size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node;

	if (!head)
		return (NULL);
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}
/**
 * add_node_end - adds node to the end of list_t list_str
 * @head: double pointer to head
 * @str: str argument of node
 * @num: index of node used by history
 *
 * Return: list size
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node_tmp;

	if (!head)
		return (NULL);
	node_tmp = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node_tmp)
	{
		while (node_tmp->next)
			node_tmp = node_tmp->next;
		node_tmp->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}
/**
 * print_str_list - prints str element of a list_t only
 * @head: pointer to first node
 *
 * Return: list size
 */
size_t print_str_list(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}
/**
 * delete_node_at_idx - deletes node at a specific index
 * @head: pointer to pointer to head
 * @idx: idx of node to delete at
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_idx(list_t **head, unsigned int idx)
{
	list_t *node_t, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
	if (!idx)
	{
		node_t = *head;
		*head = (*head)->next;
		free(node_t->str);
		free(node_t);
		return (1);
	}
	node_t = *head;
	while (node_t)
	{
		if (i == idx)
		{
			prev_node->next = node_t->next;
			free(node_t->str);
			free(node_t);
			return (1);
		}
		i++;
		prev_node = node_t;
		node_t = node_t->next;
	}
	return (0);
}
/**
 * free_str_list - frees all nodes of a list
 * @head: pointer to pointer to head
 *
 * Return: void
 */
void free_str_list(list_t **head)
{
	list_t *node_t, *next_node, *head_ptr;

	if (!head || !*head)
		return;
	head_ptr = *head;
	node_t = head_ptr;
	while (node_t)
	{
		next_node = node_t->next;
		free(node_t->str);
		free(node_t);
		node_t = next_node;
	}
	*head = NULL;
}
