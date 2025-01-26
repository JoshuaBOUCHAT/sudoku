#ifndef SUDOKU_H
#define SUDOKU_H

typedef struct _sudoku
{
    short row_usage[9];
    short col_usage[9];
    short grid_usage[9];
    char board[9][9];
} sudoku;

void init_sudoku(sudoku *s);
void display_sudoku(sudoku *s);
void from_grid(sudoku *s, int grid[9][9]);
short get_available_repr(sudoku *s, int x, int y);
int solve(sudoku *s);
void from_string(sudoku *s, char *str);
// int linear_solver(sudoku *s);

#endif