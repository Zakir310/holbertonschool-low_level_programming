#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * malloc_checked - allocates memory using malloc
 * @b: number of bytes to allocate
 *
 * Return: pointer to the allocated memory, or exit with status 98 if malloc fails
 */
void *malloc_checked(unsigned int b)
{
	void *ptr;
	ptr = malloc(b);
	if (ptr == NULL)
	{
		exit(98);
	}
	return (ptr);
}
/**
 * string_nconcat - concatenates two strings, allocating memory for the new string
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to concatenate from s2
 *
 * Return: pointer to the newly allocated concatenated string, or NULL on failure
 */
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	char *result;
	unsigned int len1 = 0, len2 = 0, i;

	while (s1 && s1[len1])
		len1++;
	while (s2 && s2[len2])
		len2++;

	if (n >= len2)
		n = len2;

	result = malloc_checked(len1 + n + 1);
	if (!result)
		return (NULL);

	for (i = 0; i < len1; i++)
		result[i] = s1[i];
	for (i = 0; i < n; i++)
		result[len1 + i] = s2[i];
	result[len1 + n] = '\0';

	return (result);
}
