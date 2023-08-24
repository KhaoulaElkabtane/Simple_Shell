#include "shell.h"

/**
 * historyfile - Generate history file path.
 * @in: Pointer to the shell information struct.
 *
 * Return: Pointer to the generated history file path or NULL on failure.
 */

char *historyfile(infocmd *in)
{
	char *buffer, *d;

	d = getVarEnv(in, "HOME=");
	if (!d)
		return (NULL);
	buffer = malloc(sizeof(char) * (strlength(d) + strlength(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	strcopy(buffer, d);
	strCat(buffer, "/");
	strCat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * creathistory - Create history file.
 * @in: Pointer to the shell information struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int creathistory(infocmd *in)
{
	ssize_t file;
	char *name = historyfile(in);
	liststr *c = NULL;

	if (!name)
		return (-1);

	file = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name);
	if (file == -1)
		return (-1);
	for (c = in->history; c; c = c->next)
	{
		putsfile2(c->s, file);
		putfile('\n', file);
	}
	putfile(BUF_FLUSH, file);
	close(file);
	return (1);
}

/**
 * readHistory - Read history from file and populate list.
 * @in: Pointer to the shell information struct.
 *
 * Return: Number of history entries read and added to the list.
 */
int readHistory(infocmd *in)
{
	int i, lt = 0, lcount = 0;
	ssize_t file, len, sz = 0;
	struct stat str;
	char *buffer = NULL, *name = historyfile(in);

	if (!name)
		return (0);

	file = open(name, O_RDONLY);
	free(name);
	if (file == -1)
		return (0);
	if (!fstat(file, &str))
		sz = str.st_size;
	if (sz < 2)
		return (0);
	buffer = malloc(sizeof(char) * (sz + 1));
	if (!buffer)
		return (0);
	len = read(file, buffer, sz);
	buffer[sz] = 0;
	if (len <= 0)
		return (free(buffer), 0);
	close(file);
	for (i = 0; i < sz; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			buildHistoList(in, buffer + lt, lcount++);
			lt = i + 1;
		}
	if (lt != i)
		buildHistoList(in, buffer + lt, lcount++);
	free(buffer);
	in->histcount = lcount;
	while (in->histcount-- >= HIST_MAX)
		delNodeIndex(&(in->history), 0);
	renumHistory(in);
	return (in->histcount);
}

/**
 * buildHistoList - Build command history list.
 * @in: Pointer to the shell information struct.
 * @buffer: Command string to be added to history.
 * @lcount: Line number of the command in the history file.
 *
 * Return: 0 on success.
 */
int buildHistoList(infocmd *in, char *buffer, int lcount)
{
	liststr *str = NULL;

	if (in->history)
		str = in->history;
	addEndNode(&str, buffer, lcount);

	if (!in->history)
		in->history = str;
	return (0);
}

/**
 * renumHistory - Renumber history list entries.
 * @in: Pointer to the shell information struct.
 *
 * Return: New history count after renumbering.
 */
int renumHistory(infocmd *in)
{
	liststr *str = in->history;
	int i = 0;

	while (str)
	{
		str->n = i++;
		str = str->next;
	}
	return (in->histcount = i);
}
