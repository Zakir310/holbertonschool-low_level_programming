#include "dog.h"
#include <stdlib.h>

/**
 * free_dog - libere la memoire d'un chien
 * @d: le chien a liberer
 *
 * Return: rien
 */
void free_dog(dog_t *d)
{
	if (d == NULL)
		return;

	free(d->name);
	free(d->owner);
	free(d);
}
