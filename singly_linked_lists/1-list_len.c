#include "lists.h"

/**
 * list_len - counts the elements of a list
 * @h: first node
 *
 * Return: number of elements
 */
size_t list_len(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		n++;
		h = h->next;
	}
	return (n);
}
