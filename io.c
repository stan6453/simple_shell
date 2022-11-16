#include "main.h"

/**
 * print_to_fd - outputs a string to a file descriptor
 * @fd: file secriptor to print to
 * @string: string to print
 * Return: number of character written
 */
size_t print_to_fd(int fd, char *string)
{
	size_t i;

	for (i = 0; string[i] != '\0'; i++)
	{
		write(fd, string + i, 1);
	}
	return (i);
}



/**
 * print_to_stdout - outputs a string to standard output
 * @string: string to print
 * Return: number of character written
 */

size_t print_to_stdout(char *string)
{
	return (print_to_fd(1, string));
}



/**
 * print_to_stderr - outputs a string to standard error
 * @string: string to print
 * Return: number of character written
 */
size_t print_to_stderr(char *string)
{
	return (print_to_fd(2, string));
}





/**
 * _getline - set the value of an environment variable
 * @str: name of env variable to set the value
 * @n: value to be set
 * @stream: if set to true, environment variabl
 * Return: 0 on seccess, -1 on failure (with err
 */
size_t _getline(char **str, size_t *n, FILE *stream)
{
	char buf[1024];
	size_t num;

	num = read(stream->_fileno, buf, 1024);

	if (num == 0)
	{
		return (0);
	}
	else if (num < 0)
	{
		return (-1);
	}
	else if (num > *n)
	{
		*str = _realloc(*str, *n, num + 1);
	}

	/*might need to free previous value stord in *str*/
	_strcpy(*str, buf);
	(*str)[num] = '\0';
	*n = num;
	return (num);
}
