#include "main.h"

/**
 * remove_quotes - unsets the value of an environment variable
 * @commandarray: name of the environment variable to unset
 */
void remove_quotes(char *commandarray[])
{
	int i;

	for (i = 1; commandarray[i] != NULL; i++)
	{
		remove_single_quotes(commandarray[i]);
	}
}



/**
 * remove_single_quotes - unsets the value of an environment variable
 * @str: name of the environment variable to unset
 */

void remove_single_quotes(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '\'')
			delete_char_at_index(str, i);
	}
}
