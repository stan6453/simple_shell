#ifndef _STANG_
#define _STANG_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>



typedef struct b_cmd {
	char *command_name;
	int (*func)(char **, char **);
} command_object;


typedef struct alias_obj{
	char *command;
	char *replacement;
} alias_t;



void executeshell(int, char **, char **);
void shell_startup_script(void);
void display_welcome_art(void);
void eval_execute_command_loop(int, char **, char **);
void displaycwd(void);
char *getusercommand(void);
void removecomment(char *);
void tokenize_string(char *command, char *commandarray[], char sep);
size_t _getline(char **str, size_t *n, FILE *stream);
int handle_builtin_commands(char **, char **);
int (*get_func_to_execute(char *commandarray[]))(char *commandarray[], char **);
void execute_user_command(char *, char **, char **);
void convert_to_argv(char *, char **);
void printarr(char *arr[]);
char *resolve_path(char *, char *, char *);
int isonlydigit(char *);
int _str_len(const char *str);
char *_getrnv(const char *name);
int comp_env_with_val(const char *env, const char *val);
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);



int exit_command(char **, char **);
int env_command(char **, char **);
int cd_command(char **, char **);
int alias_command(char **, char **);
#endif
