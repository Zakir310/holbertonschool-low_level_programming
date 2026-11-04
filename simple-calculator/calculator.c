#include <stdio.h>

/**
 * main - calculatrice : addition (1), soustraction (2), multiplication (3),
 * division (4) ; 0 quitte
 *
 * Note : les nombres sont des décimaux (double), donc 10 / 4 = 2.5.
 * Une division par zéro affiche "Error: division by zero".
 *
 * Return: 0 (succès)
 */
int main(void)
{
    int choice;
    double a;
    double b;

    printf("Simple Calculator\n");
    while (1)
    {
        printf("1) Add\n");
        printf("2) Subtract\n");
        printf("3) Multiply\n");
        printf("4) Divide\n");
        printf("0) Quit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        if (choice == 0)
        {
            printf("Bye!\n");
            break;
        }
        if (choice >= 1 && choice <= 4)
        {
            printf("A: ");
            scanf("%lf", &a);
            printf("B: ");
            scanf("%lf", &b);
        }
        if (choice == 1)
            printf("Result: %g\n", a + b);
        else if (choice == 2)
            printf("Result: %g\n", a - b);
        else if (choice == 3)
            printf("Result: %g\n", a * b);
        else if (choice == 4)
        {
            if (b == 0)
                printf("Error: division by zero\n");
            else
                printf("Result: %g\n", a / b);
        }
        else
            printf("Invalid choice\n");
    }
    return (0);
}
