#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - Struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - Single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - Single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - Singl linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Built in struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

sep_list *myadd_sep_node_end(sep_list **head, char sep);
void myfree_sep_list(sep_list **head);
line_list *myadd_line_node_end(line_list **head, char *line);
void myfree_line_list(line_list **head);

r_var *myadd_rvar_node(r_var **head, int lvar, char *var, int lval);
void myfree_rvar_list(r_var **head);

char *_mystrcat(char *dest, const char *src);
char *_mystrcpy(char *dest, char *src);
int _mystrcmp(char *s1, char *s2);
char *_mystrchr(char *s, char c);
int _mystrspn(char *s, char *accept);

void _mymemcpy(void *newptr, const void *ptr, unsigned int size);
void *_myrealloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_myreallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

char *_mystrdup(const char *s);
int _mystrlen(const char *s);
int mycmp_chars(char str[], const char *delim);
char *_mystrtok(char str[], const char *delim);
int _myisdigit(const char *s);

void myrev_string(char *s);

int myrepeated_char(char *input, int i);
int myerror_sep_op(char *input, int i, char last);
int myfirst_char(char *input, int *i);
void myprint_syntax_error(data_shell *datash, char *input, int i, int bool);
int mycheck_syntax_error(data_shell *datash, char *input);

char *mywithout_comment(char *in);
void myshell_loop(data_shell *datash);

char *myread_line(int *i_eof);

char *myswap_char(char *input, int bool);
void myadd_nodes(sep_list **head_s, line_list **head_l, char *input);
void mygo_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int mysplit_commands(data_shell *datash, char *input);
char **mysplit_line(char *input);

void mycheck_env(r_var **h, char *in, data_shell *data);
int mycheck_vars(r_var **h, char *in, char *st, data_shell *data);
char *myreplaced_input(r_var **head, char *input, char *new_input, int nlen);
char *myrep_var(char *input, data_shell *datash);

void mybring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t myget_line(char **lineptr, size_t *n, FILE *stream);

int myexec_line(data_shell *datash);

int myis_cdir(char *path, int *i);
char *_mywhich(char *cmd, char **_environ);
int myis_executable(data_shell *datash);
int mycheck_error_cmd(char *dir, data_shell *datash);
int mycmd_exec(data_shell *datash);

char *_mygetenv(const char *name, char **_environ);
int _myenv(data_shell *datash);

char *mycopy_info(char *name, char *value);
void myset_env(char *name, char *value, data_shell *datash);
int _mysetenv(data_shell *datash);
int _myunsetenv(data_shell *datash);

void mycd_dot(data_shell *datash);
void mycd_to(data_shell *datash);
void mycd_previous(data_shell *datash);
void mycd_to_home(data_shell *datash);

int mycd_shell(data_shell *datash);

int (*myget_builtin(char *cmd))(data_shell *datash);

int myexit_shell(data_shell *datash);

int myget_len(int n);
char *myaux_itoa(int n);
int _myatoi(char *s);

char *mystrcat_cd(data_shell *, char *, char *, char *);
char *myerror_get_cd(data_shell *datash);
char *myerror_not_found(data_shell *datash);
char *myerror_exit_shell(data_shell *datash);

char *myerror_get_alias(char **args);
char *myerror_env(data_shell *datash);
char *myerror_syntax(char **args);
char *myerror_permission(char **args);
char *myerror_path_126(data_shell *datash);

int myget_error(data_shell *datash, int eval);

void myget_sigint(int sig);

void myaux_help_env(void);
void myaux_help_setenv(void);
void myaux_help_unsetenv(void);
void myaux_help_general(void);
void myaux_help_exit(void);

void myaux_help(void);
void myaux_help_alias(void);
void myaux_help_cd(void);

int myget_help(data_shell *datash);

#endif
