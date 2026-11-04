#include "main.h"

/**
 * _strspn - compte combien de caractères du début de s sont dans accept
 * @s: la chaîne à analyser
 * @accept: les caractères autorisés
 *
 * Return: le nombre de caractères du début de s qui sont dans accept
 */
unsigned int _strspn(char *s, char *accept)
{
	unsigned int count;
	int i;
	int trouve;

	count = 0;
	while (s[count] != '\0')
	{
		trouve = 0;
		i = 0;
		while (accept[i] != '\0')
		{
			if (s[count] == accept[i])
				trouve = 1;
			i++;
		}
		if (trouve == 0)
			return (count);
		count++;
	}

	return (count);
}
