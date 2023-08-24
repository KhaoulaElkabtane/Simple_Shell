#include "shell.h"

/**
 * printHistory - print history list
 * @info: Structure containing arguments.
 *
 *  Return: Always 0
 */
int printHistory(infocmd *info)
{
	printList(info->history);
	return (0);
}

/**
 * unsetAlias - uset alias
 * @info: struct infocmd
 * @s: alias string
 *
 * Return: 0 if ok, 1 if fails
 */
int unsetAlias(infocmd *info, char *s)
{
	char *p, c;
	int ret;

	p = strFindchar(s, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delNodeIndex(&(info->alias),
		nodeIndex(info->alias, nodeStart(info->alias, s, -1)));
	*p = c;
	return (ret);
}

/**
 * setAlias - set alias
 * @info: struct info cmd
 * @s: alias string
 *
 * Return: 0 if ok, 1 if fails
 */
int setAlias(infocmd *info, char *s)
{
	char *p;

	p = strFindchar(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsetAlias(info, s));

	unsetAlias(info, s);
	return (addEndNode(&(info->alias), s, 0) == NULL);
}

/**
 * printAlias - prints an alias string
 * @n: alias node
 *
 * Return: 0 if ok, 1 if fails
 */
int printAlias(liststr *n)
{
	char *pt = NULL, *a = NULL;

	if (n)
	{
		pt = strFindchar(n->s, '=');
		for (a = n->s; a <= pt; a++)
			_putchar(*a);
		_putchar('\'');
		strputs(pt + 1);
		strputs("'\n");
		return (0);
	}
	return (1);
}

/**
 * manAlias - man alias
 * @info: Structure containing arguments.
 *
 *  Return: Always 0
 */
int manAlias(infocmd *info)
{
	int i = 0;
	char *p = NULL;
	liststr *n = NULL;

	if (info->argc == 1)
	{
		n = info->alias;
		while (n)
		{
			printAlias(n);
			n = n->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = strFindchar(info->argv[i], '=');
		if (p)
			setAlias(info, info->argv[i]);
		else
			printAlias(nodeStart(info->alias, info->argv[i], '='));
	}

	return (0);
}
