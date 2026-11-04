#include "main.h"
#include <stddef.h>

/**
 * _strpbrk - cherche le 1er caractère de s qui est aussi dans accept
 * @s: la chaîne où chercher
 * @accept: les caractères à trouver
 *
 * Return: un pointeur vers ce caractère dans s, ou NULL si aucun
 */
char *_strpbrk(char *s, char *accept)
{
	int i;
	int j;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (accept[j] != '\0')
		{
			if (s[i] == accept[j])
				return (&s[i]);
			j++;
		}
		i++;
	}

	return (NULL);
}
