#include "main.h"
#include <stdio.h>

/**
 * print_diagsums - affiche la somme des deux diagonales d'une matrice carrée
 * @a: la matrice, rangée en une seule suite de nombres
 * @size: le nombre de lignes (et de colonnes)
 *
 * Return: rien
 */
void print_diagsums(int *a, int size)
{
	int i;
	int somme1;
	int somme2;

	somme1 = 0;
	somme2 = 0;
	for (i = 0; i < size; i++)
	{
		somme1 = somme1 + a[i * size + i];
		somme2 = somme2 + a[i * size + (size - 1 - i)];
	}

	printf("%d, %d\n", somme1, somme2);
}


