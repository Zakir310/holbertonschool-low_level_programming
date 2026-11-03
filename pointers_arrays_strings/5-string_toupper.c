#include "main.h"

/**
 * string_toupper - met toutes les minuscules d'une chaîne en majuscules
 * @s: la chaîne à modifier
 *
 * Return: le pointeur vers s
 */
char *string_toupper(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] = s[i] - 32;
		i++;
	}

	return (s);
}
