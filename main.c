#include "shell.h"
/**
 * main - main function (run program)
 * @argc: command arguments count
 * @argv: command argument vector array
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_errputs(argv[0]);
				_errputs(": 0: Can't open ");
				_errputs(argv[1]);
				_err_putchar('\n');
				_err_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->rd_fd = fd;
	}
	populate_env_ll(info);
	read_hist(info);
	hsh_func(info, argv);
	return (EXIT_SUCCESS);
}
