#include "shell.h"

/**
 * fctActive - Check if the shell is running in an active mode.
 * @in: Pointer to infocmd struct.
 *
  * Return: 1 if active, else 0.
 */
int fctActive(infocmd *in)
{
	return (isatty(STDIN_FILENO) && in->readfd <= 2);
}

/**
 * fctDelim - Check if a character is a delimiter.
 * @str: Character to be checked.
 * @del: String of delimiters to compare against.
 *
 * Return: 1 if 'str' is a delimiter, else 0.
 */
int fctDelim(char str, char *del)
{
	while (*del)
		if (*del++ == str)
			return (1);
	return (0);
}

/**
 * fctAlphabetic - Check if a value represents an alphabetic character.
 * @alp: Value to be checked.
 *
 * Return: 1 if 'alp' is alphabetic, else 0.
 */

int fctAlphabetic(int alp)
{
	if ((alp >= 'a' && alp <= 'z') || (alp >= 'A' && alp <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * fctConv - Convert a string to an integer.
 * @str: Pointer to the input string.
 *
 * Return: The converted integer value.
 */

int fctConv(char *str)
{
	int i, sg = 1, fl = 0, put;
	unsigned int res = 0;

	for (i = 0;  str[i] != '\0' && fl != 2; i++)
	{
		if (str[i] == '-')
			sg *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			fl = 1;
			res *= 10;
			res += (str[i] - '0');
		}
		else if (fl == 1)
			fl = 2;
	}

	if (sg == -1)
		put = -res;
	else
		put = res;

	return (put);
}

