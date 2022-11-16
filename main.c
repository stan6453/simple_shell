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
 * eval_execute_command_loop - continuously asks
 * user for command and executes it
 * @argc: argument count when shell was opened
 * @argv: arguments passed to shell when it was opened
 * @env: environment variables of shell
 */
void eval_execute_command_loop(int argc __attribute__((unused)), char *argv[], char *env[])
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
