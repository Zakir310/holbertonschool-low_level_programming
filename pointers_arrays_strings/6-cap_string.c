#include "main.h"

/**
 * is_separator - vérifie si un caractère sépare deux mots
 * @c: le caractère à tester
 *
 * Return: 1 si c'est un séparateur, 0 sinon
 */
int is_separator(char c)
{
	char *sep;
	int i;

	sep = " \t\n,;.!?\"(){}";
	i = 0;
	while (sep[i] != '\0')
	{
		if (c == sep[i])
			return (1);
		i++;
	}
	return (0);
}

/**
 * cap_string - met en majuscule la 1re lettre de chaque mot
 * @s: la chaîne à modifier
 *
 * Return: le pointeur vers s
 */
char *cap_string(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] >= 'a' && s[i] <= 'z')
		{
			if (i == 0 || is_separator(s[i - 1]))
				s[i] = s[i] - 32;
		}
		i++;
	}

	return (s);
}
