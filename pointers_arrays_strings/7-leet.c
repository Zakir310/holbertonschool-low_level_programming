#include "main.h"

/**
 * leet - remplace certaines lettres par des chiffres (1337)
 * @s: la chaîne à modifier
 *
 * Return: le pointeur vers s
 */
char *leet(char *s)
{
	char *lettres;
	char *chiffres;
	int i;
	int j;

	lettres = "aAeEoOtTlL";
	chiffres = "4433007711";

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (lettres[j] != '\0')
		{
			if (s[i] == lettres[j])
				s[i] = chiffres[j];
			j++;
		}
		i++;
	}

	return (s);
}
