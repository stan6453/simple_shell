#include "main.h"

/**
 * convert_to_argv - takes a command string at tokenizes it,
 * storing each text delimited by space in commandarray
 * @command: string to get commandarray from
 * @commandarray: array of char ped by space character
 */

void convert_to_argv(char *command, char *commandarray[])
{
	int i;
	int count_ca = 0;
	int pass_space = 1;
	int pt = 0;

	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == '\'' && pt == 0)
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


/**
 * resolve_path - return the absolute path where a command can be found
 * @myprog: name of my shell
 * @progname: name of the command to execute
 * @pathvar: a pointer to the path environment variable
 * Return: nothing
 */

char *resolve_path(char *myprog, char *progname, char *pathvar)
{
	struct stat sfile;
	char *path;
	char *fullpath;
	char *copyofpathvar = malloc(100);

	if (stat(progname, &sfile) != -1)
	{
		fullpath = malloc(100);
		_strcpy(fullpath, progname);
		return (fullpath);
	}

	_strcpy(copyofpathvar, pathvar);
	path = strtok(copyofpathvar, ":");
	while (path != NULL)
	{
		fullpath = malloc(100);
		_strcpy(fullpath, path);
		_strcat(fullpath, "/");
		_strcat(fullpath, progname);
		if (stat(fullpath, &sfile) != -1)
			return (fullpath);
		path = strtok(NULL, ":");
		free(fullpath);
	}

	dprintf(2, "%s: ", myprog);
	perror("");
	return (NULL);
}




/**
 * execute_user_command - forks a process and execute command
 * on the child process using execve
 * @myprog: name of my shell
 * @myargv: synthetic commandarray for the program to run
 * @env: environment variables
 */


void execute_user_command(char *myprog, char *myargv[], char *env[])
{
	char *path_to_command;

	path_to_command = resolve_path(myprog, myargv[0], _getenv("PATH", env));
	if (path_to_command == NULL)
		return;
	if (fork() == 0)
	{
		execve(path_to_command, myargv, env);
	}
	else
	{
		free(path_to_command);
		wait(NULL);
	}
}



/**
 * handle_builtin_commands - exectutes the shell commands
 * @commandarray: argument count
 * @env: environment variables
 * Return: Always 0;
 */
int handle_builtin_commands(char *commandarray[], char *env[])
{
	int (*func)(char **, char **);

	func = get_fun(commandarray);
	if (func != NULL)
	{
		func(commandarray, env);
		return (1);
	}
	return (0);
}



/**
 * getusercommand - gets user command
 * Return: string
 */
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

	return (buf);

}
