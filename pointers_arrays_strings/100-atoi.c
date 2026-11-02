#include "main.h"

/**
 * _atoi - convertit une chaîne en entier
 * @s: la chaîne à convertir
 *
 * Return: le nombre trouvé, ou 0 s'il n'y en a pas
 */
int _atoi(char *s)
{
	int i;
	int sign;
	int res;

	i = 0;
	sign = 1;
	res = 0;

	while (s[i] != '\0' && (s[i] < '0' || s[i] > '9'))
	{
		if (s[i] == '-')
			sign = -sign;
		i++;
	}

	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 - (s[i] - '0');
		i++;
	}

	if (sign == 1)
		res = -res;

	return (res);
}
