#include "sudoku.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int grid[9][9] = {
    {8, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 3, 6, 0, 0, 0, 0, 0},
    {0, 7, 0, 0, 9, 0, 2, 0, 0},
    {0, 5, 0, 0, 0, 7, 0, 0, 0},
    {0, 0, 0, 0, 4, 5, 7, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 3, 0},
    {0, 0, 1, 0, 0, 0, 0, 6, 8},
    {0, 0, 8, 5, 0, 0, 0, 1, 0},
    {0, 9, 0, 0, 0, 0, 4, 0, 0}};

int main(void)
{
    sudoku s;
    init_sudoku(&s);
    from_grid(&s, grid);
    clock_t start = clock();
    for (int i = 0; i < 10000; i++)
    {

        sudoku test;
        memcpy(&test, &s, sizeof(sudoku));
        solve(&test);
    }
    clock_t elasped = 1000.0 * (double)(clock() - start) / (double)CLOCKS_PER_SEC;
    printf("Time to compute: %ld", elasped);

    return 0;
}