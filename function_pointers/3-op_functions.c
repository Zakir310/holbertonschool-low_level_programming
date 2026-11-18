#include "3-calc.h"

/**
 * op_add - adds a and b
 * @a: first number
 * @b: second number
 *
 * Return: the sum
 */
int op_add(int a, int b)
{
	return (a + b);
}

/**
 * op_sub - subtracts b from a
 * @a: first number
 * @b: second number
 *
 * Return: the difference
 */
int op_sub(int a, int b)
{
	return (a - b);
}

/**
 * op_mul - multiplies a and b
 * @a: first number
 * @b: second number
 *
 * Return: the product
 */
int op_mul(int a, int b)
{
	return (a * b);
}

/**
 * op_div - divides a by b
 * @a: first number
 * @b: second number
 *
 * Return: the result
 */
int op_div(int a, int b)
{
	return (a / b);
}

/**
 * op_mod - remainder of a divided by b
 * @a: first number
 * @b: second number
 *
 * Return: the remainder
 */
int op_mod(int a, int b)
{
	return (a % b);
}
