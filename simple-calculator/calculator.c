k#include <stdio.h>

/**
 * main - affiche le menu en boucle, effectue l'addition (1),
 * la soustraction (2) et la multiplication (3)
 *
 * Return: 0 (succès)
 */
int main(void)
{
    int choice;
    int a;
    int b;

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
        if (choice == 1)
        {
            printf("A: ");
            scanf("%d", &a);
            printf("B: ");
            scanf("%d", &b);
            printf("Result: %d\n", a + b);
        }
        else if (choice == 2)
        {
            printf("A: ");
            scanf("%d", &a);
            printf("B: ");
            scanf("%d", &b);
            printf("Result: %d\n", a - b);
        }
        else if (choice == 3)
        {
            printf("A: ");
            scanf("%d", &a);
            printf("B: ");
            scanf("%d", &b);
            printf("Result: %d\n", a * b);
        }
        else if (choice < 0 || choice > 4)
            printf("Invalid choice\n");
    }
    return (0);
}
