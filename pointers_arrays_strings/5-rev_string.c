#include "main.h"

/**
 * rev_string - inverse une chaîne
 * @s: la chaîne à inverser
 *
 * Return: rien
 */
void rev_string(char *s)
{
	int debut;
	int fin;
	char tmp;

	fin = 0;
	while (s[fin] != '\0')
		fin++;
	fin--;

	debut = 0;
	while (debut < fin)
	{
		tmp = s[debut];
		s[debut] = s[fin];
		s[fin] = tmp;
		debut++;
		fin--;
	}
}
