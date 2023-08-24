#include "shell.h"

/**
 * erputs - Print a string to stderr.
 * @s: Source string to be printed.
 *
 * Return: None.
 */
void erputs(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		eputchar(s[i]);
		i++;
	}
}

/**
 * eputchar - Write a character to stderr or flush buffer.
 * @str: Character to be written or BUF_FLUSH to flush.
 *
 * Return: 1 after writing or flushing.
 */
int eputchar(char str)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (str == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (str != BUF_FLUSH)
		buffer[i++] = str;
	return (1);
}

/**
 * putfile - Write a character to a file or flush buffer.
 * @str: Character to be written or BUF_FLUSH to flush.
 * @file: File descriptor to write to.
 *
 * Return: 1 after writing or flushing.
 */
int putfile(char str, int file)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (str == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(file, buffer, i);
		i = 0;
	}
	if (str != BUF_FLUSH)
		buffer[i++] = str;
	return (1);
}

/**
 * putsfile2 - Write a string to a file.
 * @str: Source string to be written.
 * @file: File descriptor to write to.
 *
 * Return: Number of characters written.
 */
int putsfile2(char *str, int file)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += putfile(*str++, file);
	}
	return (i);
}
