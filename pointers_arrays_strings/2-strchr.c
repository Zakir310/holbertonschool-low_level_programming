#include "main.h"
#include <stddef.h>

/**
 * _strchr - cherche un caractère dans une chaîne
 * @s: la chaîne où chercher
 * @c: le caractère à trouver
 *
 * Return: un pointeur vers la 1re fois où c apparaît,
 * ou NULL si c n'est pas dans s
 */
char *_strchr(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}

	if (c == '\0')
		return (&s[i]);

	return (NULL);
}

