#ifndef SUDOKU_H
#define SUDOKU_H

typedef struct _sudoku
{
    int row_usage[9];
    int col_usage[9];
    int grid_usage[9];
    int board[9][9];
} sudoku;

void init_sudoku(sudoku *s);
void is_available(sudoku *s, int x, int y, int val);
void display_sudoku(sudoku *s);
void from_grid(sudoku *s, int grid[9][9]);
int get_available_repr(sudoku *s, int x, int y);
int solve(sudoku *s);

#endif