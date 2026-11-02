#include <unistd.h>

/**
 * _putchar - écrit le caractère c sur stdout
 * @c: le caractère à afficher
 *
 * Return: 1 si ça marche, -1 sinon
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
