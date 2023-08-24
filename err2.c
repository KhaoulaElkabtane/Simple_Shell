#include "shell.h"

/**
 * erconv - Convert a string to an integer with error handling.
 * @str: Pointer to the input string.
 *
 * Return: The converted integer value or -1 on error.
 */
int erconv(char *str)
{
	int i = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res *= 10;
			res += (str[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * erprint - Print error message to stderr.
 * @in: Pointer to infocmd struct.
 * @str: Error message string.
 *
 * Return: None.
 */
void erprint(infocmd *in, char *str)
{
	erputs(in->fname);
	erputs(": ");
	fctDecimal(in->line_count, STDERR_FILENO);
	erputs(": ");
	erputs(in->argv[0]);
	erputs(": ");
	erputs(str);
}

/**
 * fctDecimal - Print an integer in decimal format.
 * @put: Integer to be printed.
 * @file: File descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int fctDecimal(int put, int file)
{
	int (*__putchar)(char) = _putchar;
	int i, cnt = 0;
	unsigned int _abs_, c;

	if (file == STDERR_FILENO)
		__putchar = eputchar;
	if (put < 0)
	{
		_abs_ = -put;
		__putchar('-');
		cnt++;
	}
	else
		_abs_ = put;
	c = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + c / i);
			cnt++;
		}
		c %= i;
	}
	__putchar('0' + c);
	cnt++;

	return (cnt);
}

/**
 * convnumber - Convert a number to a specified base and format.
 * @m: Number to be converted.
 * @b: Base for conversion (e.g., 16 for hexadecimal).
 * @fl: Conversion format flags.
 *
 * Return: Pointer to the converted number string.
 */
char *convnumber(long int m, int b, int fl)
{
	static char *ar;
	static char buffer[50];
	char s = 0;
	char *poiter;
	unsigned long n = m;

	if (!(fl & CONVERT_UNSIGNED) && m < 0)
	{
		n = -m;
		s = '-';

	}
	ar = fl & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	poiter = &buffer[49];
	*poiter = '\0';

	do	{
		*--poiter = ar[n % b];
		n /= b;
	} while (n != 0);

	if (s)
		*--poiter = s;
	return (poiter);
}

/**
 * fctremove - Remove comments from a string buffer.
 * @buffer: Input string buffer to process.
 *
 * Return: None.
 */
void fctremove(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}
