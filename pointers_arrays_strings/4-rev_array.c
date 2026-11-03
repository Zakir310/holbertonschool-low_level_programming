#include "main.h"

/**
 * reverse_array - inverse l'ordre des éléments d'un tableau d'entiers
 * @a: le tableau
 * @n: le nombre d'éléments
 *
 * Return: rien
 */
void reverse_array(int *a, int n)
{
	int debut;
	int fin;
	int tmp;

	debut = 0;
	fin = n - 1;
	while (debut < fin)
	{
		tmp = a[debut];
		a[debut] = a[fin];
		a[fin] = tmp;
		debut++;
		fin--;
	}
}
