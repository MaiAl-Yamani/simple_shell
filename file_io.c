#include "shell.h"
/**
 * get_hist - gets the history of a file
 * @info: info_t struct
 *
 * Return: string containg history
 */
char *get_hist(info_t *info)
{
	char *buffer, *dirrec;

	dirrec = _getenv(info, "HOME=");
	if (!dirrec)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dirrec) + _strlen(HIST_F) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dirrec);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_F);

	return (buffer);
}
/**
 * write_hist - creates a file, or appends to an existing one
 * @info: info_t struct
 *
 * Return: 1 on success, -1 otherwise
 */
int write_hist(info_t *info)
{
	ssize_t fd;
	char *fname = get_hist(info);
	list_t *node = NULL;

	if (!fname)
		return (-1);
	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fd == -1)
		return (-1);
	for (node = info->hist; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * read_hist - reads history from a file
 * @info: info_t struct
 *
 * Return: hist_cnt on success, 0 otherwise
 */
int read_hist(info_t *info)
{

	ssize_t fd, read_len, fsize = 0;
	char *buffer = NULL, *fname = get_hist(info);
	int lst = 0, i, linecnt = 0;
	struct stat st;

	if (!fname)
		return (0);
	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	read_len = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (read_len <= 0)
		return (free(buffer), 0);
	close(fd);

	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_hist_list(info, buffer + lst, linecnt++);
			lst = i + 1;
		}
	if (lst != i)
		build_hist_list(info, buffer + lst, linecnt++);
	free(buffer);
	info->histcnt = linecnt;
	while (info->histcnt-- >= HIST_MAX)
		delete_node_at_idx(&(info->hist), 0);
	re_number_hist(info);
	return (info->histcnt);
}
/**
 * build_hist_list - builds hist ll
 * @info: info_t struct
 * @buffer: buffer
 * @linecnt: line count for history, histcnt
 *
 * Return: Always 0
 */
int build_hist_list(info_t *info, char *buffer, int linecnt)
{
	list_t *node = NULL;

	if (info->hist)
		node = info->hist;
	add_node_end(&node, buffer, linecnt);
	if (!info->hist)
		info->hist = node;
	return (0);
}
/**
 * re_number_hist - renumbers history ll
 * @info: info_t struct
 *
 * Return: histcnt after changes
 */
int re_number_hist(info_t *info)
{
	list_t *node = info->hist;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcnt = i);
}
