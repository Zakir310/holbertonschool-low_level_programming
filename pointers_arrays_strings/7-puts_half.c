#include "main.h"

/**
 * puts_half - affiche la deuxième moitié d'une chaîne
 * @str: la chaîne à afficher
 *
 * Return: rien
 */
void puts_half(char *str)
{
	int len;
	int i;

	len = 0;
	while (str[len] != '\0')
		len++;

	i = (len + 1) / 2;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
	_putchar('\n');
}
