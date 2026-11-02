#include "main.h"

/**
 * _strcpy - copie une chaîne dans une autre
 * @dest: là où on copie
 * @src: la chaîne à copier
 *
 * Return: le pointeur vers dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}
