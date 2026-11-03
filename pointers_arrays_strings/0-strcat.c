#include "main.h"

/**
 * _strcat - colle la chaîne src à la fin de dest
 * @dest: la chaîne de départ
 * @src: la chaîne à ajouter
 *
 * Return: le pointeur vers dest
 */
char *_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;

	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';

	return (dest);
}
