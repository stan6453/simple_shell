#include "main.h"



/**
 * _str_len - finds length of a string
 * @str: string to find its length
 * Description: finds length of a string (not including null character)
 * Return: length of string
 */
int _str_len(const char *str)
{
	int i;

	if (str == NULL)
		return (0);

	for (i = 0; str[i] != '\0'; i++)
		;
	return (i);
}


size_t print_to_fd(int fd, char *string){
	size_t i;

	for (i = 0; string[i] != '\0'; i++)
	{
		write(fd, string + i, 1);
	}
	return (i);
}


size_t print_to_stdout(char *string)
{
	return (print_to_fd(1, string));
}

size_t print_to_stderr(char *string)
{
	return (print_to_fd(2, string));
}

int main(int argc, char *argv[], char *env[])
{
	int size = print_to_stderr("hello my 9 worlds");
	printf("\n%d\n", size);
}





