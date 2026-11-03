#include "main.h"

/**
 * _strncat - colle au plus n caractères de src à la fin de dest
 * @dest: la chaîne de départ
 * @src: la chaîne à ajouter
 * @n: le nombre maximum de caractères à prendre dans src
 *
 * Return: le pointeur vers dest
 */
char *_strncat(char *dest, char *src, int n)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;

	j = 0;
	while (j < n && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';

	return (dest);
}
