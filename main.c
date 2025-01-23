#include "sudoku.h"
#include <stdio.h>
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

int main(int argc, char const *argv[])
{
    sudoku s;
    init_sudoku(&s);
    from_grid(&s, grid);
    display_sudoku(&s);
    for (int i = 8; i < 9; i++)
    {
        int x = i / 9;
        int y = i % 9;
        printf("%d %d:  %b %b %b %b\n", x, y, ~s.row_usage[x] & 1022, ~s.col_usage[y] & 1022, ~s.grid_usage[x / 3 * 3 + y / 3] & 1022, get_available_repr(&s, x, y));
    }
    printf("repre 0:8    %d", get_available_repr(&s, 0, 8));
    int res = solve(&s);

    printf("Solving status:%d \n", res);

    display_sudoku(&s);

    return 0;
}
