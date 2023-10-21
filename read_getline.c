#include "shell.h"
/**
 * input_buffer - buffers chain commands
 * @info: info_t struct
 * @buffer: buffer
 * @len: len var address
 *
 * Return: bytes that was read
 */
ssize_t input_buffer(info_t *info, char **buffer, size_t *len)
{
	ssize_t rd = 0;
	size_t length = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, siginthandler);
#if GETLINE
		rd = getline(buffer, &length, stdin);
#else
		rd = _getline(info, buffer, &length);
#endif
		if (rd > 0)
		{
			if ((*buffer)[rd - 1] == '\n')
			{
				(*buffer)[rd - 1] = '\0';
				rd--;
			}
			info->linecnt_flag = 1;
			rm_comments(*buffer);
			build_hist_list(info, *buffer, info->histcnt++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = rd;
				info->cmd_buffer = buffer;
			}
		}
	}
	return (rd);
}
/**
 * get_input_line - gets input without the newline
 * @info: info_t struct
 *
 * Return: read hat was read
 */
ssize_t get_input_line(info_t *info)
{
	static char *buffer;
	static size_t len, i, j;
	ssize_t rd = 0;
	char **buffer_pos = &(info->arg);
	char *p;

	_putchar(BUF_FLUSH);

	rd = input_buffer(info, &buffer, &len);
	if (rd == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i;

		check_chain(info, buffer, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buffer_type = CMD_DFLT;
		}
		*buffer_pos = p;
		return (_strlen(p));
	}
	*buffer_pos = buffer;
	return (rd);
}
/**
 * read_buffer - reads buffer
 * @info: info_t struct
 * @buffer: a buffer
 * @size: size
 *
 * Return: rd
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *size)
{
	ssize_t rd = 0;

	if (*size)
		return (0);

	rd = read(info->rd_fd, buffer, RD_BUF_SIZE);
	if (rd >= 0)
		*size = rd;

	return (rd);
}
/**
 * _getline - gets lines in STDIN
 * @info: info_t struct
 * @p: pointer to buffer
 * @len: size of preallocated pointer p buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **p, size_t *len)
{
	static char buffer[RD_BUF_SIZE];
	static size_t i, length;
	size_t k;
	ssize_t r = 0, s = 0;
	char *ptr = NULL, *new_p = NULL, *c;

	ptr = *p;
	if (ptr && len)
		s = *len;
	if (i == length)
		i = length = 0;

	r = read_buffer(info, buffer, &length);
	if (r == -1 || (r == 0 && length == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : length;
	new_p = _realloc(ptr, s, s ? s + k : k + 1);
	if (!new_p)
		return (ptr ? free(ptr), -1 : -1);
	if (s)
		_strncat(new_p, buffer + i, k - i);
	else
		_strncpy(new_p, buffer + i, k - i + 1);
	s += k - i;
	i = k;
	ptr = new_p;
	if (len)
		*len = s;
	*p = ptr;

	return (s);
}
/**
 * siginthandler - blocks ctrl C
 * @sig_n: signal number
 *
 * Return: void
 */
void siginthandler(__attribute__((unused))int sig_n)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
