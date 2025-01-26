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
void add_change(sudoku *s, int x, int y, char val)
{
    s->board[x][y] = val;
    short temp = 1 << val;
    int grid_idx = x / 3 * 3 + y / 3;
    s->row_usage[x] |= temp;
    s->col_usage[y] |= temp;
    s->grid_usage[grid_idx] |= temp;
}
void remove_change(sudoku *s, int x, int y, char val)
{
    s->board[x][y] = 0;
    short temp = ~(1 << val);
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
            char val = grid[i][j];
            if (val)
                add_change(s, i, j, val);
        }
    }
}
inline short get_available_repr(sudoku *s, int x, int y)
{
    return (~s->row_usage[x]) & (~s->col_usage[y]) & (~s->grid_usage[x / 3 * 3 + y / 3]) & 1022;
}

int solve_at(sudoku *s, int x, int y)
{
    int nx = x + (y == 8), ny = (y + 1) * (y != 8);

    if (s->board[x][y])
    {
        return solve_at(s, nx, ny);
    }
    short repr = get_available_repr(s, x, y);
    if (repr == 0)
    {
        return 0;
    }
    for (char val = 1; val < 10; val++)
    {
        if (repr & (1 << val))
        {
            add_change(s, x, y, val);
            if ((x == 8 && y == 8) || solve_at(s, nx, ny))
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

inline void from_string(sudoku *s, char *str)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            char val = str[i * 9 + j] - '0';
            if (val != 0)
                add_change(s, i, j, val);
        }
    }
}
/*typedef struct _stack_data
 {
     int pos;
     int val;
     int passed;
 } stack_data;

 int linear_solver(sudoku *s)
 {
     int stack_idx = 0;
     stack_data stack[500];
     int start = 0;
     {
         int *temp_ptr = &s->board[0][0];
         while (temp_ptr[start] != 0 && start < 81)
             start++;
     }
     if (start == 81)
     {
         // tout la grille est templie le sudoku est deja fait
         return 1;
     }

     // initialisation de la stack avec toute les valeur possible de la premier case
     int repr = get_available_repr(s, start / 9, start % 9);
     for (int val = 1; val < 10; val++)
     {
         if (repr & (1 << val))
         {
             stack[stack_idx].passed = 0;
             stack[stack_idx].pos = start;
             stack[stack_idx].val = val;
             stack_idx++;
         }
     }
     while (stack_idx > 0)
     {
         stack_data current_data = stack[--stack_idx];
         int x = current_data.pos / 9, y = current_data.pos % 9;
         int val = current_data.val;
         if (current_data.passed)
         {
             // cette partie permet de réaliser le back tracking
             remove_change(s, x, y, val);
             continue;
         }

         // on indique qu'on la deja visite
         stack[stack_idx].passed = 1;

         // on replace le ptr de la stack a la prochain case
         stack_idx++;

         // on modifie avec les valeurs de tests

         add_change(s, x, y, val);

         // calcule position prochaine data a modifie
         int next = current_data.pos;
         {
             int *temp_ptr = &s->board[0][0];
             while (temp_ptr[next] != 0 && next < 81)
                 next++;
             if (next == 81)
             {
                 return 1;
             }
         }
         int next_x = next / 9, next_y = next % 9;
         int next_repr = get_available_repr(s, next_x, next_y);
         if (next_repr == 0)
         {
             continue;
         }

         // calule tout les valeurs possible pour la prochain case vide
         for (int next_val = 1; next_val < 10; next_val++)
         {
             if (next_repr & (1 << next_val))
             {
                 stack[stack_idx].passed = 0;
                 stack[stack_idx].pos = next;
                 stack[stack_idx].val = next_val;
                 stack_idx++;
             }
         }
     }
     return 0;
 }*/