#include "main.h"
#include <stdio.h>

/**
 * print_array - affiche n éléments d'un tableau d'entiers
 * @a: le tableau
 * @n: le nombre d'éléments à afficher
 *
 * Return: rien
 */
void print_array(int *a, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		if (i > 0)
			printf(", ");
		printf("%d", a[i]);
	}
	printf("\n");
}
