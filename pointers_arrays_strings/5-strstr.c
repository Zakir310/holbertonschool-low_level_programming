#include "main.h"
#include <stddef.h>

/**
 * _strstr - cherche une sous-chaîne dans une chaîne
 * @haystack: la chaîne où chercher
 * @needle: la sous-chaîne à trouver
 *
 * Return: un pointeur vers le début de needle dans haystack,
 * ou NULL si needle n'est pas trouvée
 */
char *_strstr(char *haystack, char *needle)
{
	int i;
	int j;

	if (needle[0] == '\0')
		return (haystack);

	i = 0;
	while (haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] != '\0' && haystack[i + j] == needle[j])
			j++;

		if (needle[j] == '\0')
			return (&haystack[i]);
		i++;
	}

	return (NULL);
}
