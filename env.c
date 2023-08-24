#include "shell.h"

/**
 * curEnv - prints the environment
 * @info: Struct containing potential arguments
 *
 * Return: Always 0
 */
int curEnv(infocmd *info)
{
	printList(info->env);
	return (0);
}

/**
 * getVarEnv - gets the value of an environ variable
 * @info: Structure containing potential arguments
 * @name: environ name
 *
 * Return: the environ value
 */
char *getVarEnv(infocmd *info, const char *name)
{
	liststr *node = info->env;
	char *p;

	while (node)
	{
		p = startsWith(node->s, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * setEnvVal - set a environment variable
 * @i: Structure containing potential arguments
 *
 *  Return: 0 if ok 1 if fails
 */
int setEnvVal(infocmd *i)
{
	if (i->argc != 3)
	{
		erputs("Incorrect number of arguements\n");
		return (1);
	}
	if (setEnv(i, i->argv[1], i->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnvVal - unset env variable
 * @info: Structure containing arguments
 *  Return: 0 if ok 1 if fails
 */
int unsetEnvVal(infocmd *info)
{
	int i;

	if (info->argc == 1)
	{
		erputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetEnv(info, info->argv[i]);

	return (0);
}

/**
 * initEnvList - init list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int initEnvList(infocmd *info)
{
	liststr *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addEndNode(&node, environ[i], 0);
	info->env = node;
	return (0);
}
