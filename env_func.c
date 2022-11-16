#include "main.h"

/**
 * comp_env_with_val - check if val matches the name of an environment variable
 * @env: string in the form "name=value"
 * @val: this string is compared with name from the string "name=valuee"
 * Return: 0 is the strings match, 1 if they don't
 */

int comp_env_with_val(const char *env, const char *val)
{
	int i;

	for (i = 0; ; i++)
	{
		if (env[i] != val[i])
		{
			if (env[i] == '=' && val[i] == '\0')
				return (0);
			else
				return (1);
		}
	}
}



/**
 * _getenv - return a pointer to the value of an environment variable
 * @name: name of the environment variable to search for its value
 * Return: pointer to the value of an environment variable searched
 *         NULL if not found
 */
char *_getenv(const char *name)
{
	/*extern char **environ;*/
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (comp_env_with_val(environ[i], name) == 0)
		{
			return (environ[i] + _str_len(name) + 1);
		}
	}
	return (NULL);
}



/**
 * _setenv - set the value of an environment variable
 * @name: name of env variable to set the value
 * @value: value to be set
 * @overwrite: if set to true, environment variable
 * Return: 0 on success, -1 on failure (with errno
 */

int _setenv(const char *name, const char *value, int overwrite)
{
	int i, j;
	/*extern char **environ;*/
	int memsize;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (comp_env_with_val(environ[i], name) == 0)
		{
			if (overwrite)
			{
				memsize = _str_len(value) + _str_len(name) + 2;
				environ[i] = malloc(memsize);
				_strcpy(environ[i], name);
				_strcat(environ[i], "=");
				_strcat(environ[i], value);
			}
			return (0);
		}
	}

	/*
	 * add a new environment variable
	 */
}




/**
 * _unsetenv - unsets the value of an environment variable
 * @name: name of the environment variable to unset
 * Return: 0 in success, -1 on error (with errno set (not implemented yet))
 */
int _unsetenv(const char *name)
{
	/*extern char **environ;*/
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (comp_env_with_val(environ[i], name) == 0)
		{
			/*
			* delete from array
			*/
			for (; environ[i] != NULL; i++)
			{
				environ[i] = environ[i + 1];
			}
			return (0);
		}
	}
	return (0);
}
