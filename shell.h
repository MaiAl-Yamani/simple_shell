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

char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
void display_prompt(void);
void out_print(const char *msg);
void read_cmd(char *cmd, size_t size);
void execute_cmd(const char *cmd);

#endif
