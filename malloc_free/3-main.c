
#include "main.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int **grid;
    int i;

    grid = alloc_grid(6, 4);

    if (grid == NULL)
        return (1);

    for (i = 0; i < 4; i++)
    {
        free(grid[i]);
    }

    free(grid);

    return (0);
}

