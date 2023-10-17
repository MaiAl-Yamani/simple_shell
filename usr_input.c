#include "shell.h"
/**
 * read_cmd - reads command inputs from stdin
 * @cmd: command input
 * @size: size of the string array
 *
 * Return: void
 */
void read_cmd(char *cmd, size_t size)
{
	if (fgets(cmd, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			out_print("/n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			out_print("Error in reading from stdin\n");
			exit(EXIT_FAILURE);
		}
	}
	cmd[strcspn(cmd, "\n")] = '\0';
}
