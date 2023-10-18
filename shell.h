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

int _strlen(const char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(const char *str);
size_t _strcspn(const char *s1, const char *s2);
void display_prompt(void);
void out_print(const char *msg);
void read_cmd(char **cmd, size_t *size);
int is_empty_or_whitespace(const char *cmd);
void execute_cmd(const char *cmd);

#endif
