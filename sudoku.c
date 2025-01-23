#include "sudoku.h"
#include <stdio.h>

void init_sudoku(sudoku *s)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            s->board[i][j] = 0;
        }
        s->col_usage[i] = 0;
        s->grid_usage[i] = 0;
        s->row_usage[i] = 0;
    }
}
void add_change(sudoku *s, int x, int y, int val)
{
    s->board[x][y] = val;
    int temp = 1 << val;
    int grid_idx = x / 3 * 3 + y / 3;
    s->row_usage[x] |= temp;
    s->col_usage[y] |= temp;
    s->grid_usage[grid_idx] |= temp;
}
void remove_change(sudoku *s, int x, int y, int val)
{
    s->board[x][y] = 0;
    int temp = ~(1 << val);
    int grid_idx = x / 3 * 3 + y / 3;
    s->row_usage[x] &= temp;
    s->col_usage[y] &= temp;
    s->grid_usage[grid_idx] &= temp;
}
void display_sudoku(sudoku *s)
{
    printf("-------------------------------\n");
    for (int i = 0; i < 9; i++)
    {
        printf("| %c  %c  %c | %c  %c  %c | %c  %c  %c |\n",
               s->board[i][0] ? s->board[i][0] + '0' : '.',
               s->board[i][1] ? s->board[i][1] + '0' : '.',
               s->board[i][2] ? s->board[i][2] + '0' : '.',
               s->board[i][3] ? s->board[i][3] + '0' : '.',
               s->board[i][4] ? s->board[i][4] + '0' : '.',
               s->board[i][5] ? s->board[i][5] + '0' : '.',
               s->board[i][6] ? s->board[i][6] + '0' : '.',
               s->board[i][7] ? s->board[i][7] + '0' : '.',
               s->board[i][8] ? s->board[i][8] + '0' : '.');
        if (i == 2 || i == 5)
        {
            printf("-------------------------------\n");
        }
    }
    printf("-------------------------------\n");
}
void from_grid(sudoku *s, int grid[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int val = grid[i][j];
            if (val)
                add_change(s, i, j, val);
        }
    }
}
inline int get_available_repr(sudoku *s, int x, int y)
{
    return (~s->row_usage[x]) & (~s->col_usage[y]) & (~s->grid_usage[x / 3 * 3 + y / 3]) & 0b1111111110;
}
int solve_at(sudoku *s, int x, int y)
{
    int repr = get_available_repr(s, x, y);
    if (s->board[x][y])
    {
        return solve_at(s, x + (y == 8), (y + 1) % 9);
    }
    if (repr == 0)
    {
        return 0;
    }
    for (int val = 1; val < 10; val++)
    {
        if (repr & (1 << val))
        {
            add_change(s, x, y, val);
            if (x == 8 && y == 8)
            {
                return 1;
            }
            int nx = x + (y == 8), ny = (y + 1) % 9;
            if (solve_at(s, nx, ny))
            {
                return 1;
            }
            remove_change(s, x, y, val);
        }
    }
    return 0;
}
int solve(sudoku *s)
{
    return solve_at(s, 0, 0);
}