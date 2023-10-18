#include "shell.h"
/**
 * main - runs the program
 *
 * Return: always 0 (success)
 */
int main(void)
{
	char cmd[120];

	while (true)
	{
		display_prompt();
		read_cmd(cmd, sizeof(cmd));
		if (is_empty_or_whitespace(cmd))
			continue;
		if (strcmp(cmd, "exit") == 0)
			break;
		execute_cmd(cmd);
	}
	return (0);
}
