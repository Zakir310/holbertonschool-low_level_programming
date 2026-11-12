#include "main.h"
#include <stdlib.h>

/**
 * _calloc - réserve de la mémoire pour un tableau et la remplit de 0
 * @nmemb: le nombre d'éléments
 * @size: la taille d'un élément en octets
 *
 * Return: un pointeur vers la mémoire, ou NULL en cas d'échec
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	char *p;
	unsigned int i;
	unsigned int total;

	if (nmemb == 0 || size == 0)
		return (NULL);

	total = nmemb * size;
	p = malloc(total);
	if (p == NULL)
		return (NULL);

	for (i = 0; i < total; i++)
		p[i] = 0;

	return (p);
}
