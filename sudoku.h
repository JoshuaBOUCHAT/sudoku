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
inline short get_available_repr(sudoku *s, int x, int y)
{
    return (~s->row_usage[x]) & (~s->col_usage[y]) & (~s->grid_usage[x / 3 * 3 + y / 3]) & 1022;
}

#endif