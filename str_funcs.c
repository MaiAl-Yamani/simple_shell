#include "shell.h"
/**
 * _strlen - return the length of a string
 * @s: pinter to char s
 *
 * Description: returns the length of a string
 * Return: string length
 */
int _strlen(const char *s)
{
	int i = 0;

	for (; *s != '\0'; s++)
	{
		i++;
	}
	return (i);
}
/**
 * _strcat - concatinate two string variables
 * @src: the first string variable pointer to src
 * @dest: the second string variable pointer to dest
 *
 * Description: concatinate two string variables
 * Return: (dest)
 */
char *_strcat(char *dest, char *src)
{
	int dest_len = strlen(dest);
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[dest_len + i] = src[i];
	}
	dest[dest_len + i] = '\0';

	return (dest);
}
/**
 * _strcmp - compares two strings
 * @s1: pointer to 1st string
 * @s2: pointer to 2nd string
 *
 * Return: (out) 0 if s1=s2, -ve if s1<s2, +ve if s1>s2
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0, out = 0;

	while (out == 0)
	{
		if ((*(s1 + i) == '\0') && (*(s2 + i) == '\0'))
		{
			break;
		}
		out = *(s1 + i) - *(s2 + i);
		i++;
	}

	return (out);
}
/**
 * _strdup - duplicates a string
 * @str: string to be duplicated
 *
 * Return: pointer to the result string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *res;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	for (len++; len--;)
		res[len] = *--str;
	return (res);
}
/**
 * _strcspn - scans the string for first ocurrance of reject
 * @s1: 1st string
 * @s2: 2nd string
 *
 * Return: length of first segment of s1 consisting of bytes not in s2
 */
size_t _strcspn(const char *s1, const char *s2)
{
	const char *s_c1, *s_c2;

	for (s_c1 = s1; *s_c1 != '\0'; ++s_c1)
	{
		for (s_c2 = s2; *s_c2 != '\0'; ++s_c2)
		{
			if (*s_c1 == *s_c2)
				return (s_c1 - s1);
		}
	}
	return (s_c1 - s1);
}
