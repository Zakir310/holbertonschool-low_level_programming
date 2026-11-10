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
	 * string_nconcat - concatenates two strings
	 * @s1: first string
	 * @s2: second string
	 * @n: number of bytes to concatenate from s2
	 *
	 * Return: pointer to the concatenated string, or NULL if malloc fails
	 */
	char *string_nconcat(char *s1, char *s2, unsigned int n)
	{
		char *ptr;
		unsigned int i, j;

		if (s1 == NULL)
			s1 = "";
		if (s2 == NULL)
			s2 = "";

		for (i = 0; s1[i] != '\0'; i++)
			;
		for (j = 0; s2[j] != '\0' && j < n; j++)
			;

		ptr = malloc((i + j + 1) * sizeof(char));
		if (ptr == NULL)
			return (NULL);

		for (i = 0; s1[i] != '\0'; i++)
			ptr[i] = s1[i];
		for (j = 0; s2[j] != '\0' && j < n; j++)
			ptr[i + j] = s2[j];
		ptr[i + j] = '\0';

		return (ptr);
	}
