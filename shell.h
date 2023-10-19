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

/* str_funcs.c module */
int _strlen(const char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(const char *str);
size_t _strcspn(const char *s1, const char *s2);

/* prompt.c module */
void display_prompt(void);

/* print.c module */
void out_print(const char *msg);

/* usr_input.c module */
void read_cmd(FILE* file, char **cmd, size_t *size);
void read_from_keyboard(char **cmd, size_t *size);
void read_from_file(FILE* file, char **cmd, size_t *size);
int is_empty_or_whitespace(const char *cmd);

/* execute.c module */
void execute_cmd(const char *cmd);

#endif
