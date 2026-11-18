#include <stdio.h>

/**
 * main - prints the arguments passed to the program
 * @argc: number of arguments (program name included)
 * @argv: array of arguments
 *
 * Return: 0 (Success)
 */
int main(int argc, char *argv[])
{
	int i;

	for (i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
	return (0);
}
