#include "shell.h"

/**
 * **strToWords - splits a string without repeated delimiter
 * @str: the input string
 * @del: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strToWords(char *str, char *del)
{
	int i, j, k, m, nbr = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!fctDelim(str[i], del) && (fctDelim(str[i + 1], del) || !str[i + 1]))
			nbr++;

	if (nbr == 0)
		return (NULL);
	s = malloc((1 + nbr) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nbr; j++)
	{
		while (fctDelim(str[i], del))
			i++;
		k = 0;
		while (!fctDelim(str[i + k], del) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * strToWords2 - Split a string into an array of words using a delimiter.
 * @s: Input string to be split.
 * @del: Delimiter character to split the string.
 *
 * Return: an array of strings extracted from the input string or NULL if fails
 */
char **strToWords2(char *s, char del)
{
	int i, j, k, m, nbr = 0;
	char **res;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
		if ((s[i] != del && s[i + 1] == del) ||
		    (s[i] != del && !s[i + 1]) || s[i + 1] == del)
			nbr++;
	if (nbr == 0)
		return (NULL);
	res = malloc((1 + nbr) * sizeof(char *));
	if (!res)
		return (NULL);
	for (i = 0, j = 0; j < nbr; j++)
	{
		while (s[i] == del && s[i] != del)
			i++;
		k = 0;
		while (s[i + k] != del && s[i + k] && s[i + k] != del)
			k++;
		res[j] = malloc((k + 1) * sizeof(char));
		if (!res[j])
		{
			for (k = 0; k < j; k++)
				free(res[k]);
			free(res);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			res[j][m] = s[i++];
		res[j][m] = 0;
	}
	res[j] = NULL;
	return (res);
}
