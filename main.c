#include "shell.h"
/**
 * main - runs the program
 *
 * Return: always 0 (success)
 */
int main(void)
{
	char *cmd = NULL;
	size_t cmd_size = 0;

	while (true)
	{
		display_prompt();
		read_cmd(&cmd, &cmd_size);
		if (is_empty_or_whitespace(cmd))
			continue;
		if (strcmp(cmd, "exit") == 0)
			break;
		execute_cmd(cmd);
	}
	free(cmd);
	return (0);
}
