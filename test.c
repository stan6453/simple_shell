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

void tokenize_string (char *command, char *commandarray[], char sep)
{
	int i;
	int count_ca = 0;
	int pass_space = 1;

	for (i = 0; command[i] != '\0'; i++)
	{
		if (pass_space == 1 && command[i] != sep)
		{
			commandarray[count_ca] = command + i;
			count_ca++;
			pass_space = 0;
		}
		else if (command[i] == sep && pass_space != 1)
		{
			command[i] = '\0';
			pass_space = 1;
		}

	}

	commandarray[count_ca] = NULL;
}





int main(int argc, char *argv[], char *env[])
{
	char *stringarr[6];
	char string[] = "ls -al";
	tokenize_string(string, stringarr, ';');

	int i = 0;

	while (stringarr[i] != NULL)
	{
		printf("%s\n", stringarr[i]);
		i++;
	}
	return 1;
}





