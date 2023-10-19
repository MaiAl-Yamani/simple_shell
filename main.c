#include "shell.h"
/**
 * main - runs the program
 * @argc: number of arguments
 * @argv: arguments array
 *
 * Return: always 0 (success)
 */
int main(int argc, char *argv[])
{
	char *cmd = NULL;
	FILE *file = NULL;
	size_t cmd_size = 0;

	if (argc > 1)
	{
		file = fopen(argv[1], "r");
		if (file == NULL)
		{
			perror("Error opening file");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		file = stdin;
	}
	while (true)
	{
		display_prompt();
		/*printf("%s \n", cmd);*/
		/*printf("%ld \n", cmd_size);*/
		read_cmd(file, &cmd, &cmd_size);
		if (is_empty_or_whitespace(cmd))
			continue;
		if (strcmp(cmd, "exit") == 0)
			break;
		execute_cmd(cmd);
		if (!isatty(STDIN_FILENO))
		{
			break;
		}
	}
	if (file != NULL)
	{
		fclose(file);
	}
	free(cmd);
	return (0);
}
