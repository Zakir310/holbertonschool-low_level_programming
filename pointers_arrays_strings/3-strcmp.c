#include "main.h"

/**
 * _strcmp - compare deux chaînes
 * @s1: la première chaîne
 * @s2: la deuxième chaîne
 *
 * Return: 0 si elles sont égales, sinon la différence
 * entre les premiers caractères différents
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;

	return (s1[i] - s2[i]);
}
