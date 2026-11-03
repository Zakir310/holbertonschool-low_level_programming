#include "main.h"

/**
 * _memset - remplit les n premiers octets de s avec l'octet b
 * @s: la zone mémoire à remplir
 * @b: l'octet à écrire
 * @n: le nombre d'octets à remplir
 *
 * Return: le pointeur vers s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		s[i] = b;
		i++;
	}

	return (s);
}

