#include "shell.h"

/**
 **strNcopy - make a copy of a string
 *@d: string 1
 *@s: string 2
 *@nbr: number of characters to be copied in d
 *Return: string
 */
char *strNcopy(char *d, char *s, int nbr)
{
	int i, j;
	char *res = d;

	i = 0;
	while (s[i] != '\0' && i < nbr - 1)
	{
		d[i] = s[i];
		i++;
	}
	if (i < nbr)
	{
		j = i;
		while (j < nbr)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (res);
}

/**
 **strNcat - concatenates two strings
 *@d: string 1
 *@src: string 2
 *@nbr: number of characters to be used
 *Return: the concatenated string
 */
char *strNcat(char *d, char *src, int nbr)
{
	int i, j;
	char *s = d;

	i = 0;
	j = 0;
	while (d[i] != '\0')
		i++;
	while (src[j] != '\0' && j < nbr)
	{
		d[i] = src[j];
		i++;
		j++;
	}
	if (j < nbr)
		d[i] = '\0';
	return (s);
}

/**
 * strFindchar - find a character in a string
 * @str: string
 * @f: character
 * Return: pointer
 */
char *strFindchar(char *str, char f)
{
	do {
		if (*str == f)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
