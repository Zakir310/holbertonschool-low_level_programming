#include "main.h"

/**
 * print_rev - affiche une chaîne à l'envers, puis un retour à la ligne
 * @s: la chaîne à afficher
 *
 * Return: rien
 */
void print_rev(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;

	while (i > 0)
	{
		i--;
		_putchar(s[i]);
	}
	_putchar('\n');
}
