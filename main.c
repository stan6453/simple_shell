#include "main.h"
/**
 * main - exectutes the shell commands
 * @argc: argument count
 * @argv: array of argument variables
 * @env: environment variables
 * return: Always 0;
 */
int main(int argc, char *argv[], char *env[])
{
	executeshell(argc, argv, env);
	return (0);
}

/**
 * executeshell - receives commands passed to the shell
 * and executes them
 * @argc: argument count
 * @argv: array of argument variables
 * @env: environment variables
 * return: void;
 */

void executeshell(int argc, char *argv[], char *env[])
{
	shell_startup_script();
	eval_execute_command_loop(argc, argv, env);

}

/**
 * shell_startup_script - displays welcome message to screen
 * return: void;
 */
void shell_startup_script(void)
{
	display_welcome_art();
}


/**
 * display_welcome_art - reads welcome art from art.txt
 * and displays to screen
 * return: void;
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
 * eval_execute_command_loop - continuously asks user for command and executes it 
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

	while(1)
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
 * remove_quotes - used to remove all quotes from the options of the shell command
 * @commandarray: array of string pointers to remove quote from
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
 * remove_single_quotes - removes all single quote character in a string
 * @str: the sring to remove single quotes from
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
 * delete_char_at_index - delete a character from a particular index in a string
 * @str: string to delete character from
 * @index: position of the character to remove
 */
void delete_char_at_index(char *str, int index)
{
	while (str[index] != '\0')
	{
		str[index] = str[index + 1];
		index++;
	}
}

/*
void replace_variables(char *commandarray[])
{
	int i;

	for (i = 1; commandarray[i] != NULL; i++)
	{
		if (commandarray[i][0] == '$' && commandarray[i][1] != '\n')
		{
			switch(commandarray[i][1])
			{
				case '?':
					return;
				case '$':
					_strcpy(commandarray[i], num_to_string(getpid()));
					return;
				default:
					return;
			}
		}
	}
}

*/


/**
 * removecomment - remove singlre line comment (#) from the command
 * @str: string to remove comment from
 * @index: position of the character to remove
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



void displaycwd(void)
{
	char CWD[256];
	printf("%s$ ", getcwd(CWD, 256));
	fflush(stdout);
}




char *getusercommand(void)
{
	char *buf = NULL;
	size_t bufsize = 0;
	size_t numchar;

	numchar = _getline(&buf, &bufsize, stdin);

	if (numchar == 0)
	{
		exit(-1);
	}

	if (buf[numchar - 1] == '\n')
		buf[numchar - 1] = '\0';

	return buf;

}


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

	_strcpy(*str, buf);
	(*str)[num] = '\0';
	*n = num;
	return num;
}




int handle_builtin_commands(char *commandarray[], char *env[])
{
	int (*func)(char **, char **);
	func = get_func_to_execute(commandarray);
	if (func != NULL)
	{
		func(commandarray, env);
		return (1);
	}

	return (0);
}


int (*get_func_to_execute(char *commandarray[]))(char *commandarray[], char *env[])
{
	int i;

	command_object array[] =
	{
		{"exit", exit_command},
		{"env", env_command},
		{"cd", cd_command},
		{"alias", alias_command},
		{NULL, NULL}
	};

	for (i = 0; array[i].command_name != NULL; i++ )
	{
		if (_strcmp(array[i].command_name, commandarray[0]) == 0)
			return (array[i].func);
	}

	return (NULL);
}

int alias_command (char *commandarray[], char *env[])
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

void display_or_update_aliases(char *commandarray[], alias_t aliases[])
{
	int i;

	for (i = 1; commandarray[i] != NULL; i++)
	{
		if(does_str_contain(commandarray[i], '='))
		{
			updatealiases(commandarray[i], aliases);
		}
		else
		{
			//display this alias
		}
	}
}

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


void updatealiases(char *str, alias_t aliases[])
{
	int i;
	int index;
	char *cnr[3];
	alias_t newalias;

	cnr[2] = NULL;

	tokenize_string(str, cnr, '=');

	index = get_alias_index(aliases, cnr[0]);

	if (index >=0)
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

//return alias index in success
//return -1 on failure
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


void execute_user_command(char *myprog, char *myargv[], char *env[])
{
	struct stat sfile;
	char *path_to_command;

	path_to_command = resolve_path(myprog, myargv[0], _getenv("PATH"));
	if (path_to_command == NULL)
		return;
	if (fork() == 0)
	{
		execve(path_to_command, myargv, NULL);
	}
	else
	{
		free(path_to_command);
		wait(NULL);
	}
}



void convert_to_argv(char *command, char *commandarray[])
{
	int i;
	int count_ca = 0;
	int pass_space = 1;
	int pt = 0;

	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == '\'' && pt == 0 )
			pt = 1;
		else if (command[i] == '\'' && pt == 1)
			pt = 0;

		if (pass_space == 1 && command[i] != ' ')
		{
			commandarray[count_ca] = command + i;
			count_ca++;
			pass_space = 0;
		}
		else if (command[i] == ' ' && pass_space != 1 && pt == 0)
		{
			command[i] = '\0';
			pass_space = 1;
		}

	}

	commandarray[count_ca] = NULL;
}


void printarr(char *arr[])
{
	while (*arr != NULL)
	{
		printf("%s\n", *arr);
		arr++;
	}
}


char *resolve_path(char *myprog, char *progname, char *pathvar)
{
	struct stat sfile;
	char *path;
	char *fullpath;
	char *copyofpathvar = malloc(100);

	_strcpy(copyofpathvar, pathvar);
	path = strtok(copyofpathvar, ":");
	while(path != NULL){
		fullpath = malloc(100);
		_strcpy(fullpath, path);
		_strcat(fullpath, "/");
		_strcat(fullpath, progname);
		if(stat(fullpath, &sfile) != -1)
			return fullpath;
		path = strtok(NULL, ":");
		free(fullpath);
	}

	dprintf(2, "%s: ", myprog);
	perror("");
	return NULL;
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




int comp_env_with_val(const char *env, const char *val)
{
	int i;

	for (i = 0; ; i++){
		if(env[i] != val[i])
		{
			if (env[i] == '=' && val[i] == '\0')
				return (0);
			else
				return(1);
		}
	}
}


char *_getenv(const char *name)
{
	extern char **environ;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (comp_env_with_val(environ[i], name) == 0)
		{
			return (environ[i] + _str_len(name) + 1);
		}
	}

}




int _setenv(const char *name, const char *value, int overwrite)
{
	int i, j;
	extern char **environ;
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

				return (0);
			}
			return (0);
		}
	}

	/*
	 * add a new environment variable
	 */
}


int _unsetenv(const char *name)
{
	extern char **environ;
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



/**
 * _atoi -  convert a string to an integer
 * @s: the sting to convert to integer
 * Description:  convert a string of numbers to an integer
 * Return: integer gotten from string
 */
int _atoi(char *s)
{
	int i, n, sign = 1, no_of_dash = 0;

	/* skip any character that is not a number*/
	for (i = 0; s[i] < '0' || s[i] > '9'; i++)
	{
		if (s[i] == '\0')
			return (0);
		if (s[i] == '-')
			no_of_dash++;
	}

	sign = (no_of_dash % 2 == 0) ? 1 : -1;
	for (n = 0; s[i] >= '0' && s[i] <= '9'; i++)
		n = 10 * n + (s[i] - '0');
	return (sign * n);
}


/**
 * _strcpy - copy source string to a destination sting
 * @dest: string to copy to
 * @src: string to copy from
 * Description: copy's the contents of a source string to a destination string
 * Return: the destination string
 */
char *_strcpy(char *dest, const char *src)
{
	int index;
	int letter;

	for (index = 0; ((letter = src[index]) != '\0'); index++)
	{
		dest[index] = letter;
	}
	dest[index] = letter;
	return (dest);
}



/**
 * _strcmp - multiplies two digits
 * @s1: 1st digit in the multiplication
 * @s2: 1st digit in the multiplication
 * Description: multiplies two digits
 * Return: the result of the multiplication
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (1)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return (s1[i] - s2[i]);
		i++;
	}
}



/**
 * _strcat - multiplies two digits
 * @src: 1st digit in the multiplication
 * @dest: 2nd digit to be multiplied
 * Description: multiplies two digits
 * Return: the result of the multiplication
 */
char *_strcat(char *dest, const char *src)
{
	int i, j;

	i = 0;
	j = 0;
	while (dest[i] != '\0') /* find end of dest */
		i++;
	while ((dest[i++] = src[j++]) != '\0') /* copy src */
		;
	return (dest);
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
