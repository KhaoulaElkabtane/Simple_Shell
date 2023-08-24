#include "shell.h"

/**
 * lislength - Calculate the length of a linked list.
 * @len: Pointer to the start of the linked list.
 *
 * Return: Number of elements in the linked list.
 */
size_t lislength(const liststr *len)
{
	size_t i = 0;

	while (len)
	{
		len = len->next;
		i++;
	}
	return (i);
}

/**
 * listString - Convert linked list to array of strings.
 * @str: Pointer to the start of the linked list.
 *
 * Return: Array of strings converted from linked list.
 */
char **listString(liststr *str)
{
	liststr *no = str;
	size_t i = lislength(str), j;
	char **c;
	char *st;

	if (!str || !i)
		return (NULL);
	c = malloc(sizeof(char *) * (i + 1));
	if (!c)
		return (NULL);
	for (i = 0; no; no = no->next, i++)
	{
		st = malloc(strlength(no->s) + 1);
		if (!st)
		{
			for (j = 0; j < i; j++)
				free(c[j]);
			free(c);
			return (NULL);
		}

		st = strcopy(st, no->s);
		c[i] = st;
	}
	c[i] = NULL;
	return (c);
}


/**
 * fctlist - Print a linked list of numbers and strings.
 * @lt: Pointer to the start of the linked list.
 *
 * Return: Number of elements printed.
 */
size_t fctlist(const liststr *lt)
{
	size_t i = 0;

	while (lt)
	{
		strputs(convnumber(lt->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		strputs(lt->s ? lt->s : "(nil)");
		strputs("\n");
		lt = lt->next;
		i++;
	}
	return (i);
}

/**
 * nodeStart - Find a linked list node that starts with a given string.
 * @st: Pointer to the start of the linked list.
 * @ch: String to search for at the beginning of a node's string.
 * @str: Character to match at the start of the found node's string.
 *
 * Return: Pointer to the found node or NULL if not found.
 */
liststr *nodeStart(liststr *st, char *ch, char str)
{
	char *k = NULL;

	while (st)
	{
		k = startsWith(st->s, ch);
		if (k && ((str == -1) || (*k == str)))
			return (st);
		st = st->next;
	}
	return (NULL);
}

/**
 * nodeIndex - Find the index of a linked list node.
 * @in: Pointer to the start of the linked list.
 * @dex: Pointer to the node to find the index for.
 *
 * Return: Index of the found node or -1 if not found.
 */
ssize_t nodeIndex(liststr *in, liststr *dex)
{
	size_t i = 0;

	while (in)
	{
		if (in == dex)
			return (i);
		in = in->next;
		i++;
	}
	return (-1);
}
