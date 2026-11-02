#include "main.h"

/**
 * _strlen - renvoie la longueur d'une chaîne
 * @s: la chaîne à mesurer
 *
 * Return: le nombre de caractères de s
 */
int _strlen(char *s)
{
	int len;

	len = 0;
	while (s[len] != '\0')
		len++;

	return (len);
}
