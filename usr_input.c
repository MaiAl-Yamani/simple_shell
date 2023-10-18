#include "shell.h"
/**
 * read_cmd - reads command inputs from stdin
 * @cmd: command input
 * @size: size of the string array
 *
 * Return: void
 */
void read_cmd(char **cmd, size_t *size)
{
	ssize_t r;

	r = getline(cmd, size, stdin);
	if (r == -1)
	{
		if (feof(stdin))
		{
			out_print("/n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			out_print("Error in reading\n");
			exit(EXIT_FAILURE);
		}
	}
	(*cmd)[_strcspn(*cmd, "\n")] = '\0';
}
/**
 * is_empty_or_whitespace - checks if the command is empty or whitespace
 * @cmd: command input
 *
 * Return: 1 if empty or whitespace, 0 otherwise
 */
int is_empty_or_whitespace(const char *cmd)
{
	int i;

	for (i = 0; cmd[i] != '\0'; i++)
	{
		if ((cmd[i] != '\n') && (cmd[i] != ' ') && (cmd[i] != '\t'))
			return (false);
	}
	return (true);
}
