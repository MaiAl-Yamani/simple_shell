#include "shell.h"
/**
 **_memset - fills memory with constant byte
 *@s_ptr: pointer to memory area
 *@byte: byte to fill with
 *@n: amount of bytes to be filled
 *Return: pointer to the memory area s_ptr
 */
char *_memset(char *s_ptr, char byte, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s_ptr[i] = byte;
	return (s_ptr);
}
/**
 * ffree - frees a string of strings
 * @ptrptr: string of strings
 *
 * Return: void
 */
void ffree(char **ptrptr)
{
	char **ar = ptrptr;

	if (!ptrptr)
		return;
	while (*ptrptr)
		free(*ptrptr++);
	free(ar);
}
/**
 * _realloc - reallocates memory
 * @p: pointer to previous memory allocated block
 * @old_mem_size: previous block size
 * @new_mem_size: new block size
 *
 * Return: pointer
 */
void *_realloc(void *p, unsigned int old_mem_size, unsigned int new_mem_size)
{
	char *ptr;

	if (!p)
		return (malloc(new_mem_size));
	if (!new_mem_size)
		return (free(p), NULL);
	if (new_mem_size == old_mem_size)
		return (p);
	ptr = malloc(new_mem_size);
	if (!ptr)
		return (NULL);
	old_mem_size = old_mem_size < new_mem_size ? old_mem_size : new_mem_size;
	while (old_mem_size--)
		ptr[old_mem_size] = ((char *)p)[old_mem_size];
	free(p);
	return (ptr);
}
/**
 * bfree - frees a pointer and sets address to NULL
 * @p: pointer address
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
