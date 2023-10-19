#include "shell.h"
/**
 * read_cmd - reads commands
 * @file: file of type FILE that the cmd is read from
 * @cmd: command input
 * @size: size of string array
 *
 * Return: void
 */
void read_cmd(FILE *file, char **cmd, size_t *size)
{
	if (isatty(STDIN_FILENO))
	{
		/* interactive mode */
		read_from_keyboard(cmd, size);
	}
	else
	{
		/* non-interactive mode */
		read_from_file(file, cmd, size);
	}
}
/**
 * read_from_keyboard - reads command inputs from keyboard
 * @cmd: command input
 * @size: size of the string array
 *
 * Return: void
 */
void read_from_keyboard(char **cmd, size_t *size)
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
			out_print("Error in reading from keyboard\n");
			exit(EXIT_FAILURE);
		}
	}
	(*cmd)[_strcspn(*cmd, "\n")] = '\0';
}
/**
 * read_from_file - reads command from file in non-interactive
 * @file: file to read from
 * @cmd: command input
 * @size: size of command array
 *
 * Return: void
 */
void read_from_file(FILE *file, char **cmd, size_t *size)
{
	ssize_t r;

	/*out_print("inside read_from_file\n");*/
	r = getline(cmd, size, file);
	if (r == -1)
	{
		if (feof(file))
		{
			/*out_print("\n");*/
			exit(EXIT_SUCCESS);
		}
		else
		{
			out_print("Error in reading from file\n");
			exit(EXIT_FAILURE);
		}
	}
	(*cmd)[strcspn(*cmd, "\n")] = '\0';
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
