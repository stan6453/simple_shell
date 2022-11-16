#include "main.h"
/**
 * main - exectutes the shell commands
 * @argc: argument count
 * @argv: array of argument variables
 * @env: environment variables
 * Return: Always 0;
 */
int main(int argc, char *argv[], char *env[])
{
	executeshell(argc, argv, env);
	return (0);
}

/**
 * executeshell - activates command execution loop
 * @argc: argument count
 * @argv: array of argument variables
 * @env: environment variables
 * Return: void;
 */

void executeshell(int argc, char *argv[], char *env[])
{
	shell_startup_script();
	eval_execute_command_loop(argc, argv, env);

}

/**
 * shell_startup_script - displays welcome message to screen
 * Return: void;
 */
void shell_startup_script(void)
{
	display_welcome_art();
}


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
 * eval_execute_command_loop - continuously asks
 * user for command and executes it
 * @argc: argument count when shell was opened
 * @argv: arguments passed to shell when it was opened
 * @env: environment variables of shell
 */
void eval_execute_command_loop(int argc, char *argv[], char *env[])
{
	char *usercommand;
	char *commandarray[10];
	char *commandsep[10];
	int i;

	while (1)
	{
		displaycwd();
		usercommand = getusercommand();
		removecomment(usercommand);
		i = 0;
		if (*usercommand == '\0')
			continue;
		tokenize_string(usercommand, commandsep, ';');
		while (commandsep[i] != NULL)
		{
			convert_to_argv(commandsep[i], commandarray);
			/*replace_variables(commandarray);*/
			if (handle_builtin_commands(commandarray, env) == 1)
			{
				i++;
				continue;
			}
			execute_user_command(argv[0], commandarray, env);
			i++;
		}
		free(usercommand);
	}
}





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



/**
 * delete_char_at_index - outputs a string to a file descriptor
 * @str: file secriptor to print to
 * @index: string to print
 * Return: number of character written
 */

void delete_char_at_index(char *str, int index)
{
	while (str[index] != '\0')
	{
		str[index] = str[index + 1];
		index++;
	}
}









/**
 * displaycwd - gets user command
 */
void displaycwd(void)
{
	char CWD[256];

	printf("%s$ ", getcwd(CWD, 256));
	fflush(stdout);
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





/**
 * exit_command - exectutes the shell commands
 * @commandarray: argument count
 * @env: environment variables
 * Return: Always 0;
 */


int exit_command(char *commandarray[], char *env[])
{
	if (!isonlydigit(commandarray[1]))
	{
		dprintf(2, "Illegal number: %s\n", commandarray[1]);
		return (1);
	}
	else
		exit(_atoi(commandarray[1]));
}






/**
 * env_command - fn that runs when the env comamnd is executed
 * @commandarray: array containing the name of the command and its options
 * @env: environment variables
 * Return: honestly, this fn doesnt really need to return anything (my bad)
 */
int env_command(char *commandarray[], char *env[])
{
	int i = 0;

	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (1);
}


/**
 * cd_command - fn that runs when the cd comamnd is executed
 * @commandarray: array containing the name of the command and its options
 * @env: environment variables
 * Return: honestly, this fn doesnt really need to return anything (my bad)
 */
int cd_command(char *commandarray[], char *env[])
{
	char CWD[256];
	char *_CWD;
	char *_OCWD = getcwd(CWD, 256);

	if (commandarray[1] == NULL)
	{
		if (chdir(_getenv("HOME")) == 0)
		{
			_setenv("PWD", _getenv("HOME"), 1);
			_setenv("OLDPWD", _OCWD, 1);
			return (1);
		}
		return (1);
	}
	else if (_strcmp(commandarray[1], "-") == 0)
	{
		_CWD = _getenv("OLDPWD");
		if (chdir(_CWD) == 0)
		{
			_setenv("PWD", _CWD, 1);
			-setenv("OLDPWD", _OCWD, 1);
			return (0);
		}
		return (0);
	}
	_CWD = commandarray[1];
	if (chdir(commandarray[1]) == 0)
	{
		_setenv("PWD", _CWD, 1);
		_setenv("OLDPWD", _OCWD, 1);
	}
	return (1);
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
