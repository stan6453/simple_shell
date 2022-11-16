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
