#include "main.h"

/**
 * _atoi -  convert a string to an integer
 * @s: the sting to convert to integer
 * Description:  convert a string of numbers to an integer
 * Return: integer gotten from string
 */
int _atoi(char *s)
{
	int i, n, sign = 1, no_of_dash = 0;

	/* skip any character that is not a number*/
	for (i = 0; s[i] < '0' || s[i] > '9'; i++)
	{
		if (s[i] == '\0')
			return (0);
		if (s[i] == '-')
			no_of_dash++;
	}

	sign = (no_of_dash % 2 == 0) ? 1 : -1;
	for (n = 0; s[i] >= '0' && s[i] <= '9'; i++)
		n = 10 * n + (s[i] - '0');
	return (sign * n);
}


/**
 * _strcpy - copy source string to a destination sting
 * @dest: string to copy to
 * @src: string to copy from
 * Description: copy's the contents of a source string to a destination string
 * Return: the destination string
 */
char *_strcpy(char *dest, const char *src)
{
	int index;
	int letter;

	for (index = 0; ((letter = src[index]) != '\0'); index++)
	{
		dest[index] = letter;
	}
	dest[index] = letter;
	return (dest);
}



/**
 * _strcmp - multiplies two digits
 * @s1: 1st digit in the multiplication
 * @s2: 1st digit in the multiplication
 * Description: multiplies two digits
 * Return: the result of the multiplication
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (1)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return (s1[i] - s2[i]);
		i++;
	}
}



/**
 * _strcat - multiplies two digits
 * @src: 1st digit in the multiplication
 * @dest: 2nd digit to be multiplied
 * Description: multiplies two digits
 * Return: the result of the multiplication
 */
char *_strcat(char *dest, const char *src)
{
	int i, j;

	i = 0;
	j = 0;
	while (dest[i] != '\0') /* find end of dest */
		i++;
	while ((dest[i++] = src[j++]) != '\0') /* copy src */
		;
	return (dest);
}






/**
 * does_str_contain - outputs a string to a file descriptor
 * @str: file secriptor to print to
 * @letter: string to print
 * Return: number of character written
 */
int does_str_contain(char *str, char letter)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == letter)
			return (1);
	}
	return (0);
}
