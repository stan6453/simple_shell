/**
 * displayaliases - unsets the value of an environment variable
 * @aliases: name of the environment variable to unset
 * Return: 0 in success, -1 on error (with errno set (not implemented yet))
 */
void displayaliases(alias_t aliases[])
{
	int i;

	for (i = 0; aliases[i].command != NULL; i++)
	{
		print_to_stdout(aliases[i].command);
		print_to_stdout("=");
		print_to_stdout(aliases[i].replacement);
		print_to_stdout("\n");
	}
}



/**
 * updatealiases - unsets the value of an environment variable
 * @str: name of the environment variable to unset
 * @aliases: whatever
 * Return: 0 in success, -1 on error (with errno set (not implemented yet))
 */
void updatealiases(char *str, alias_t aliases[])
{
	int i;
	int index;
	/*command and replacement*/
	char *cnr[3];
	alias_t newalias;

	cnr[2] = NULL;

	tokenize_string(str, cnr, '=');

	index = get_alias_index(aliases, cnr[0]);

	if (index >= 0)
	{
		free(aliases[index].replacement);
		aliases[index].replacement = malloc(_str_len(cnr[1]) + 1);
		_strcpy(aliases[index].replacement, cnr[1]);
	}
	else
	{
		newalias.command = malloc(_str_len(cnr[0]) + 1);
		newalias.replacement = malloc(_str_len(cnr[1]) + 1);

		for (i = 0; aliases[i].command != NULL; i++)
			;

		aliases[i + 1] = aliases[i];
		aliases[i] = newalias;
	}

}



/**
 * get_alias_index - exectutes the shell commands
 * @aliases: argument count
 * @name: array of argument variables
 * Return: Always 0;
 */

int get_alias_index(alias_t aliases[], char *name)
{
	int i;

	for (i = 0; aliases[i].command != NULL; i++)
	{
		if (_strcmp(aliases[i].command, name) == 0)
			return (i);
	}

	return (-1);
}




/**
 * display_or_update_aliases - outputs a string to a file descriptor
 * @commandarray: file secriptor to print to
 * @aliases: string to print
 * Return: number of character written
 */

void display_or_update_aliases(char *commandarray[], alias_t aliases[])
{
	int i;

	for (i = 1; commandarray[i] != NULL; i++)
	{
		if (does_str_contain(commandarray[i], '='))
		{
			updatealiases(commandarray[i], aliases);
		}
		else
		{
			/*display this alias*/
		}
	}
}





/**
 * alias_command - outputs a string to a file descriptor
 * @commandarray: file secriptor to print to
 * @env: string to print
 * Return: number of character written
 */
int alias_command(char *commandarray[], char *env[])
{
	static alias_t aliases[100] = {
		{"love", "love command"},
		{"hate", "madara_uchiha"},
		{NULL, NULL}
	};
	int i;

	for (i = 0; commandarray[i] != NULL; i++)
		;

	if (i == 1)
		displayaliases(aliases);

	if (i > 1)
		display_or_update_aliases(commandarray, aliases);

}
