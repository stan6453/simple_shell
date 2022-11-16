#include "main.h"

/**
 * display_welcome_art - reads welcome art from art.txt
 * and displays to screen
 * Return: void;
 */

void display_welcome_art(void)
{
	int fd = open("art.txt", O_RDONLY, 0);
	char buf[1020];
	int n;

	while ((n = read(fd, buf, 1020)) != 0)
		write(1, buf, n);
	printf("\n");
}



/**
 * displaycwd - gets user command
 */
void displaycwd(void)
{
	char prompt[] = "$ ";
	write(STDOUT_FILENO, &prompt, 2);
}


/**
 * get_fun - the nvironment variable
 * @commandarray: name of the eniable to unset
 * Return: 0 in success, -1 on error (with er
 */

int (*get_fun(char *commandarray[]))(char *commandarray[], char *env[])
{
	int i;

	command_object array[] = {
		{"exit", exit_command},
		{"env", env_command},
		{"cd", cd_command},
		{"alias", alias_command},
		{NULL, NULL}
	};

	for (i = 0; array[i].command_name != NULL; i++)
	{
		if (_strcmp(array[i].command_name, commandarray[0]) == 0)
			return (array[i].func);
	}

	return (NULL);
}




/**
 * _realloc - multiplies two digits
 * @ptr: 1st digit in the multiplication
 * @old_size: 1st digit in the multiplication
 * @new_size: 1st digit in the multiplication
 * Description: multiplies two digits
 * Return: the result of the multiplication
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	char *new_ptr;
	char *ptr2 = ptr;

	if (ptr == NULL)
	{
		new_ptr = (malloc(new_size));
		if (new_ptr == NULL)
			return (NULL);
		return (new_ptr);
	}

	if (new_size == 0)
	{
		if (ptr != NULL)
			free(ptr);
		ptr = NULL;
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);

	new_ptr = (char *)malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	/*copy from old_size to new_size*/
	for (i = 0; i < new_size && i < old_size; i++)
	{
		new_ptr[i] = ptr2[i];
	}
	free(ptr);
	ptr = NULL;
	ptr2 = NULL;
	return (new_ptr);
}
