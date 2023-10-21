#include "shell.h"
/**
 * **strtow - string into words.
 * @s: string
 * @delim: delimeter
 *
 * Return: pointer to an array of strings, or NULL
 */
char **strtow(char *s, char *delim)
{
	int i, j, k, m, words = 0;
	char **str;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; s[i] != '\0'; i++)
		if (!is_delim(s[i], delim)
				&& (is_delim(s[i + 1], delim) || !s[i + 1]))
			words++;
	if (words == 0)
		return (NULL);
	str = malloc((1 + words) * sizeof(char *));
	if (!str)
		return (NULL);
	for (i = 0, j = 0; j < words; j++)
	{
		while (is_delim(s[i], delim))
			i++;
		k = 0;
		while (!is_delim(s[i + k], delim) && s[i + k])
			k++;
		str[j] = malloc((k + 1) * sizeof(char));
		if (!str[j])
		{
			for (k = 0; k < j; k++)
				free(str[k]);
			free(str);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			str[j][m] = s[i++];
		str[j][m] = 0;
	}
	str[j] = NULL;
	return (str);
}
/**
 * **strtow2 - string into words
 * @s: string
 * @delim: delimeter
 *
 * Return: pointer to an array of strings, or NULL
 */
char **strtow2(char *s, char delim)
{
	int i, j, k, m, words = 0;
	char **str;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
		if ((s[i] != delim && s[i + 1] == delim) ||
		    (s[i] != delim && !s[i + 1]) || s[i + 1] == delim)
			words++;
	if (words == 0)
		return (NULL);
	str = malloc((1 + words) * sizeof(char *));
	if (!str)
		return (NULL);
	for (i = 0, j = 0; j < words; j++)
	{
		while (s[i] == delim && s[i] != delim)
			i++;
		k = 0;
		while (s[i + k] != delim && s[i + k] && s[i + k] != delim)
			k++;
		str[j] = malloc((k + 1) * sizeof(char));
		if (!str[j])
		{
			for (k = 0; k < j; k++)
				free(str[k]);
			free(str);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			str[j][m] = s[i++];
		str[j][m] = 0;
	}
	str[j] = NULL;
	return (str);
}
/**
 * _strncpy - copies a string
 * @dest: string
 * @src: string
 * @n_size: number of chars to be copied
 * Return: concat string
 */
char *_strncpy(char *dest, char *src, int n_size)
{
	int i, j;
	char *str = dest;

	i = 0;
	while (src[i] != '\0' && i < n_size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n_size)
	{
		j = i;
		while (j < n_size)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (str);
}
/**
 * *_strncat - concatenates 2 strings
 * @dest: string
 * @src: string
 * @n_size: max number of bytes to be used
 * Return: concat string
 */
char *_strncat(char *dest, char *src, int n_size)
{
	int i, j = 0;
	char *str = dest;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n_size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n_size)
		dest[i] = '\0';
	return (str);
}
/**
 * *_strchr - locates a ch in a str
 * @str: string
 * @ch: char
 * Return: pointer str
 */
char *_strchr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
