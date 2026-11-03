#include "main.h"

/**
 * _memcpy - copie n octets de src vers dest
 * @dest: la zone mémoire où on copie
 * @src: la zone mémoire à copier
 * @n: le nombre d'octets à copier
 *
 * Return: le pointeur vers dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}

	return (dest);
}
