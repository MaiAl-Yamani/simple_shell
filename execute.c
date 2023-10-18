#include "shell.h"
/**
 * execute_cmd - excutes the commands
 * @cmd: command inputs
 *
 * Return: void
 */
void execute_cmd(const char *cmd)
{
	/* parsing */
	char *args[120], full_path[120];
	int arg_cnt = 0, i;
	char *saveptr, *saveptr2;
	char *path_str = getenv("PATH");
	char *path_strcpy = _strdup(path_str);
	char *token_path = NULL;
	char *cmd_copy = _strdup(cmd);
	char *token = strtok_r((char *)cmd_copy, " ", &saveptr2);
	extern char **environ;
	pid_t child_pid;

	while (token != NULL)
	{
		args[arg_cnt++] = token;
		token = strtok_r(NULL, " ", &saveptr2);
	}
	args[arg_cnt++] = NULL;
	if (strcmp(args[0], "exit") == 0)
		exit(0);

	if (path_str != NULL)
	{
		token_path = strtok_r(path_strcpy, ":", &saveptr);

		while (token_path != NULL)
		{
			full_path[0] = '\0';
			_strcat(full_path, token_path);
			_strcat(full_path, "/");
			_strcat(full_path, args[0]);
			if (access(full_path, F_OK) != -1)
			{
				args[0] = full_path;
				break;
			}
			token_path = strtok_r(NULL, ":", &saveptr);
		}
	}
	if (access(args[0], F_OK) == -1)
	{
		perror("./shell");
		return;
	}

	if (access(args[0], F_OK) != -1)
	{
		child_pid = fork();
	}

	if (child_pid == -1)
	{
		out_print("Error in fork\n");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		/* currently in child process */

		/* excution */
		if (execve(args[0], args, environ) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* currently in parent process */
		wait(NULL);
		for (i = 0; i < arg_cnt; i++)
		{
			args[i] = NULL;
		}
		arg_cnt = 0;
	}
	free(cmd_copy);
	free(path_strcpy);
}
