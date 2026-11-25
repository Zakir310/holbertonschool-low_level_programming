#include <stdio.h>
#include "lists.h"

/**
 * print_list - prints all elements of a list
 * @h: first node
 *
 * Return: number of nodes
 */
size_t print_list(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		if (h->str)
			printf("[%u] %s\n", h->len, h->str);
		else
			printf("[0] (nil)\n");
		h = h->next;
		n++;
	}
	return (n);
}
