#include <stdio.h>
#include <stdlib.h>

/**
 * main - adds two numbers passed as arguments
 * @argc: number of arguments (program name included)
 * @argv: array of arguments
 *
 * Return: 0 (Success)
 */
int main(int argc, char *argv[])
{
	int num1, num2, result;

	if (argc != 3)
	{
		printf("Usage: %s <number1> <number2>\n", argv[0]);
		return (1);
	}

	num1 = atoi(argv[1]);
	num2 = atoi(argv[2]);
	result = num1 + num2;

	printf("%d\n", result);
	return (0);
}
