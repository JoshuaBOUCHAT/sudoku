#ifndef SUDOKU_H
#define SUDOKU_H

typedef struct _sudoku
{
    short row_usage[9];
    short col_usage[9];
    short grid_usage[9];
    char board[9][9];
} sudoku;

void display_sudoku(sudoku *s);
int solve(sudoku *s);
sudoku from_string(char *str);

#endif