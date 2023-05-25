#ifndef _MAIN_H_
#define _MAIN_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR	        1
#define CMD_AND	        2
#define CMD_CHAIN       3

/* 1 if using system getline() */
#define USE_GETLINE	0
#define USE_STRTOK	0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * structr passinfo - contains pseudo-arguments to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecout_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* _shellLoop.c */
int find_builtin(info_t *);
int hsh(info_t *, char **);
void fork_cmd(info_t *);
void find_cmd(info_t *);

/* _parse.c */
char *find_cmmnd_path(info_t *, char *, char *);
int is_cmmnd(info_t *, char *);
char *duplica_chars(char *, int, int);

/* loophsh.c */
int loophsh(char **);

/* errs.c */
void _sputs(char *);
int _sputchar(char);
int _cputfd(char c, int fd);
int _sputsfd(char *str, int fd);

/* _string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* _stringone.c */
void _puts(char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
int _putchar(char);

/* _exits.c */
char *_lochar(char *, char);
char *_cpynstr(char *, char * int);
char *_catnstr(char *, char *, int);

/* _tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* _reallocate.c */
char *_memoryset(char *, char, unsigned int);
void fFree(char **);
void *_reallocate(void *, unsigned int, unsigned int);

/* _memory.c */
int bFree(void **);

/* _stoi.c */
int interact(info_t *);
int is_delimit(char, char *);
int _isalphabet(int);
int _stoi(char *);

/* errsone.c */
int _errtoint(char *);
void _print_err(info_t *, char *);
int _print_dec(int, int);
char *convert_num(long int, int, int);
void rm_comments(char *);

/* _buildin.c */
int _exitme(info_t *);
int _cdme(info_t *);
int _helpme(info_t *);

/* _builtinone.c */
int _historyme(info_t *);
int _aliasme(info_t *);

/* getline.c */
ssize_t get_inputl(info_t *);
int _getnxtline(info_t *, char **, size_t *);
void siginthandle(int);

/* _getInfo.c */
void freeInfo(info_t *, int);
void clrInfo(info_t *);
void setInfo(info_t *, char **);

/* envir.c */
char *_getenvir(info_t *, const char *);
int _myenvir(info_t *);
int _mysetenvir(info_t *);
int _myunsetenvir(info_t *);
int populate_envir_list(info_t *);

/* _getENV.c */
char **get_envir(info_t *);
int _setenvir(info_t *, char *, char *);
int _unsetenvir(info_t *, char *);

/* _history.c */
char *get_file_history(info_t *info);
int w_history(info_t *info);
int r_history(info_t *info);
int b_history_list(info_t *info, char *buf, int linecount);
int renum_history(info_t *info);

/* _lists.c */
list_t *add_node_start(list_t **, const char *, int);
list_t *add_node_to_endl(list_t **, const char *, int);
size_t print_strl(const list_t *);
int delete_idx_node(list_t **, unsigned int);
void list_free(list_t **);

/* _listsone.c */
size_t ls_len(const list_t *);
char **ls_to_strings(list_t *);
size_t ls_print(const list_t *);
list_t *starts_node_with(list_t *, char *, char);
ssize_t node_index(list_t *, list_t *);

/* var.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
