#include "main.h"

/**
 * ls_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t ls_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * ls_to_strings - returns an array of strings of the list->str
 * @head: a pointer to first node
 *
 * Return: array of strings
 */
char **ls_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->strs);
		strs[i] = str;
	}
	str[i] = NULL;
	return (strs);
}

/**
 * ls_print - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: the size of list
 */
size_t ls_print(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * starts_node_with - returns node whose string starts with prefix
 * @node: a pointer to list head
 * @prefix: string to match
 * @c: next character after prefix to matcg
 *
 * Return: match node or null
 */
list_t *starts_node_with(list_t *nide, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * node_index - gets the index of a node
 * @head: a pointer to list head
 * @node: a pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
