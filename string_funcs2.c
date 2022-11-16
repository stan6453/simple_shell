/**
 * removecomment - unsets the value of an environment variable
 * @str: name of the environment variable to unset
 */
void removecomment(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == '#')
		{
			str[i] = '\0';
			return;
		}
}



/**
 * tokenize_string - set the value of an environment variable
 * @command: name of env variable to set the value
 * @commandarray: value to be set
 * @sep: if set to true, environment variable is overwri
 */
void tokenize_string(char *command, char *commandarray[], char sep)
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


/**
 * isonlydigit - checks if a string contains only digits
 * @s: string to be checked
 * Description: checks if a string contains only digit
 * Return: 1 if string contains only didgit
 *         0 if string has at lest one non-digit character
 */
int isonlydigit(char *s)
{
	while (*s != '\0')
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}



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
