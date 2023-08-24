#include "shell.h"

/**
 * strcopy - Copy a string to another.
 * @est: Destination string.
 * @sc: Source string.
 *
 * Return: Pointer to the destination string 'est'.
 */
char *strcopy(char *est, char *sc)
{
	int i = 0;

	if (est == sc || sc == 0)
		return (est);
	while (sc[i])
	{
		est[i] = sc[i];
		i++;
	}
	est[i] = 0;
	return (est);
}

/**
 * strduplicate - Create a duplicate of a string.
 * @st: Source string to be duplicated.
 *
 * Return: Pointer to the duplicated string, or NULL on failure.
 */
char *strduplicate(const char *st)
{
	int lg = 0;
	char *r;

	if (st == NULL)
		return (NULL);
	while (*st++)
		lg++;
	r = malloc(sizeof(char) * (lg + 1));
	if (!r)
		return (NULL);
	for (lg++; lg--;)
		r[lg] = *--st;
	return (r);
}

/**
 * strputs - Print a string to stdout.
 * @s: Source string to be printed.
 *
 * Return: None.
 */
void strputs(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}

/**
 * _putchar - Write a character to stdout or flush buffer.
 * @str: Character to be written or BUF_FLUSH to flush.
 *
 * Return: 1 after writing or flushing.
 */
int _putchar(char str)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (str == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (str != BUF_FLUSH)
		buffer[i++] = str;
	return (1);
}
