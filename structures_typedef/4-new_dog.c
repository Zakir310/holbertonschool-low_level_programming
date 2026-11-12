#include "dog.h"
#include <stdlib.h>

/**
 * new_dog - cree un nouveau chien
 * @name: nom du chien
 * @age: age du chien
 * @owner: proprietaire du chien
 *
 * Return: un pointeur vers le nouveau chien, ou NULL en cas d'echec
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *d;
	int ln, lo, i;

	if (name == NULL || owner == NULL)
		return (NULL);
	ln = 0;
	while (name[ln])
		ln++;
	lo = 0;
	while (owner[lo])
		lo++;
	d = malloc(sizeof(dog_t));
	if (d == NULL)
		return (NULL);
	d->name = malloc(ln + 1);
	d->owner = malloc(lo + 1);
	if (d->name == NULL || d->owner == NULL)
	{
		free(d->name);
		free(d->owner);
		free(d);
		return (NULL);
	}
	for (i = 0; i <= ln; i++)
		d->name[i] = name[i];
	for (i = 0; i <= lo; i++)
		d->owner[i] = owner[i];
	d->age = age;
	return (d);
}
