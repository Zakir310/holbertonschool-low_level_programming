#include "main.h"

/**
 * _puts - affiche une chaîne suivie d'un retour à la ligne
 * @str: la chaîne à afficher
 *
 * Return: rien
 */
void _puts(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
	_putchar('\n');
}

