#include "shell.h"

/**
 * fctCmd - Check if a given path points to a regular file.
 * @in: Pointer to the infocmd struct (not used in this function).
 * @p: Path to be checked for regular file status.
 *
 * Return: 1 if the path points to a regular file, 0 otherwise.
 */
int fctCmd(infocmd *in, char *p)
{
	struct stat str;

	(void)in;
	if (!p || stat(p, &str))
		return (0);

	if (str.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * fctduplicate - Create a duplicate substring from a given range in a string.
 * @str: Pointer to the input string.
 * @tart: Starting index of the substring.
 * @top: Ending index of the substring.
 *
 * Return: Pointer to the duplicated substring.
 */
char *fctduplicate(char *str, int tart, int top)
{
	static char buffer[1024];
	int i = 0, j = 0;

	for (j = 0, i = tart; i < top; i++)
		if (str[i] != ':')
			buffer[j++] = str[i];
	buffer[j] = 0;
	return (buffer);
}

/**
 * fctpath - Find and return the full path of a command.
 * @in: Pointer to infocmd struct.
 * @str: Colon-separated paths.
 * @cd: Command name.
 *
 * Return: Full path if found, else NULL.
 */
char *fctpath(infocmd *in, char *str, char *cd)
{
	int i = 0, position = 0;
	char *ph;

	if (!str)
		return (NULL);
	if ((strlength(cd) > 2) && startsWith(cd, "./"))
	{
		if (fctCmd(in, cd))
			return (cd);
	}
	while (1)
	{
		if (!str[i] || str[i] == ':')
		{
			ph = fctduplicate(str, position, i);
			if (!*ph)
				strCat(ph, cd);
			else
			{
				strCat(ph, "/");
				strCat(ph, cd);
			}
			if (fctCmd(in, ph))
				return (ph);
			if (!str[i])
				break;
			position = i;
		}
		i++;
	}
	return (NULL);
}
