#include "main.h"

/**
 * print_chessboard - affiche un échiquier de 8 x 8
 * @a: le tableau à deux dimensions qui contient l'échiquier
 *
 * Return: rien
 */
void print_chessboard(char (*a)[8])
{
	int ligne;
	int col;

	for (ligne = 0; ligne < 8; ligne++)
	{
		for (col = 0; col < 8; col++)
			_putchar(a[ligne][col]);
		_putchar('\n');
	}
}
