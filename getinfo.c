#include "shell.h"

/**
 * unsetInfo - initializes info_t struct
 * @info: struct address
 */
void unsetInfo(infocmd *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setInfo - init struct infocmd
 * @info: struct info cmd
 * @a: init values
 */
void setInfo(infocmd *info, char **a)
{
	int i = 0;

	info->fname = a[0];
	if (info->arg)
	{
		info->argv = strToWords(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = strduplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		repAlias(info);
		repVars(info);
	}
}

/**
 * libInfo - free infocmd struct
 * @info: pointer to struct
 * @a: true if ok
 */
void libInfo(infocmd *info, int a)
{
	strfree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (a)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeList(&(info->env));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		strfree(info->environ);
			info->environ = NULL;
		freemem((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
