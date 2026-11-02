#include "main.h"

/**
 * puts2 - affiche un caractère sur deux, puis un retour à la ligne
 * @str: la chaîne à afficher
 *
 * Return: rien
 */
void puts2(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i % 2 == 0)
			_putchar(str[i]);
		i++;
	}
	_putchar('\n');
}
