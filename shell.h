#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>

/* buffers for read and write*/
#define RD_BUF_SIZE 1024
#define WR_BUF_SIZE 1024
#define BUF_FLUSH -1

/* convert_num */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGN		2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_F		".simple_shell_history"
#define HIST_MAX	4096

/* cmd chaining */
#define CMD_DFLT	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_SEPAR	3

extern char **environ;

/**
 * struct list_str - singly linked list
 * @num: num field
 * @str: string
 * @next: next node pointer
 */
typedef struct list_str
{
	int num;
	char *str;
	struct list_str *next;
} list_t;
/**
 *struct pass_info - struct to pass different arguments into a function
 *@arg: a string by getline which includes arguements
 *@argv: an array of strings in arg
 *@path: path from currend cmd
 *@argc: arguments count
 *@line_cnt: error line count
 *@err_n: error status for exit()s
 *@linecnt_flag: flag is on if this line
 *@filename: file name of the program
 *@env: local copy of environ
 *@environ: modified copy of environ
 *@hist: history
 *@alias: alias
 *@env_change: on if environ was changed
 *@status: status of last exec command
 *@cmd_buffer: address of pointer to cmd_buf, on if chaining
 *@cmd_buffer_type: CMD_type ;, ||, &&
 *@rd_fd: file desciptor from which to read line input
 *@histcnt: history number count of the line
 */
typedef struct pass_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_cnt;
	int err_n;
	int linecnt_flag;
	char *filename;
	list_t *env;
	list_t *hist;
	list_t *alias;
	char **environ;
	int env_change;
	int status;

	char **cmd_buffer;
	int cmd_buffer_type;
	int rd_fd;
	int histcnt;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - struct for builtin commands
 * @type: command type
 * @function: corresponding function to the command
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_t;


/* hsh_main.c */
int hsh_func(info_t *, char **);
int find_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* handle_path.c */
int is_command(info_t *, char *);
char *dup_ch(char *, int, int);
char *find_path(info_t *, char *, char *);

/* str_funcs.c module */
int _strlen(const char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(const char *str);
size_t _strcspn(const char *s1, const char *s2);

/* str_funcs2.c module */
int _putchar(char ch);
void _puts(char *str);
char *start_with(const char *haystack, const char *needle);
char *_strcpy(char *dest, char *src);

/* str_funcs3.c */
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);

/* err_funcs.c module */
void _errputs(char *);
int _err_putchar(char);
int _putfd(char c, int fd);
int _putsfd(char *s, int fd);

/* mem_funcs.c module */
char *_memset(char *s_ptr, char byte, unsigned int n);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);
int bfree(void **);

/* helper_funcs.c module */
int is_interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* helper_funcs2.c */
int _err_atoi(char *);
void print_err(info_t *, char *);
int print_dec(int, int);
char *convert_num(long int, int, int);
void rm_comments(char *);

/* builtin_emulators.c */
int _hsh_exit(info_t *);
int _hsh_cd(info_t *);
int _hsh_help(info_t *);

/* builtin_emulators2.c */
int _hsh_history(info_t *);
int _hsh_alias(info_t *);

/* read_getline.c module */
ssize_t input_buffer(info_t *info, char **buffer, size_t *len);
ssize_t get_input_line(info_t *);
int _getline(info_t *, char **, size_t *);
void siginthandler(int);

/* info_struct.c module */
void clear_info_struct(info_t *);
void set_info_struct(info_t *, char **);
void free_info_struct(info_t *, int);

/* env.c module */
int _hsh_env(info_t *);
char *_getenv(info_t *, const char *);
int _hsh_setenv(info_t *);
int _hsh_unsetenv(info_t *);
int populate_env_ll(info_t *);

/* env_2.c module */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* list_str.c module */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_str_list(const list_t *);
int delete_node_at_idx(list_t **, unsigned int);
void free_str_list(list_t **);

/* liststr2.c module */
size_t listlen(const list_t *);
char **list_to_str(list_t *);
size_t print_ll(const list_t *);
list_t *node_start_prefix(list_t *, char *, char);
ssize_t get_node_idx(list_t *, list_t *);

/* file_io.c module */
char *get_hist(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int build_hist_list(info_t *info, char *buffer, int linecnt);
int re_number_hist(info_t *info);

/* chain_handle.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int alias_replace(info_t *);
int vars_replace(info_t *);
int replace_str(char **, char *);

#endif
