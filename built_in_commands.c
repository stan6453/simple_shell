#include "main.h"

/**
 * exit_command - exectutes the shell commands
 * @commandarray: argument count
 * @env: environment variables
 * Return: Always 0;
 */


int exit_command(char *commandarray[], char *env[] __attribute__((unused)))
{
	if (!isonlydigit(commandarray[1]))
	{
		print_to_stderr("Illegal number: ");
		print_to_stderr(commandarray[1]);
		print_to_stderr("\n");
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
int env_command(char *commandarray[] __attribute__((unused)), char *env[])
{
	int i = 0;

	while (env[i])
	{
		print_to_stdout(env[i]);
		print_to_stdout("\n");
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
		if (chdir(_getenv("HOME", env)) == 0)
		{
			_setenv("PWD", _getenv("HOME", env), 1);
			_setenv("OLDPWD", _OCWD, 1);
			return (1);
		}
		return (1);
	}
	else if (_strcmp(commandarray[1], "-") == 0)
	{
		_CWD = _getenv("OLDPWD", env);
		if (chdir(_CWD) == 0)
		{
			_setenv("PWD", _CWD, 1);
			_setenv("OLDPWD", _OCWD, 1);
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
