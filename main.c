#include "sudoku.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>
#include <stdlib.h>

#include <fcntl.h>

#define SIZE 10000

void solve_all(char *path);

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

char *test = "050703060007000800000816000000030000005000100730040086906000204840572093000409000";

int main(void)
{
    double start = omp_get_wtime();
    solve_all("./easy.txt");
    solve_all("./hard.txt");
    solve_all("./diabolical.txt");
    solve_all("./medium.txt");
    double end = omp_get_wtime() - start;
    printf("total time to compute is: %fs\n", end);

    return 0;
}
void solve_all(char *path)
{
    omp_set_num_threads(12);
    int fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        perror("Fichier introuvable");
        exit(EXIT_FAILURE);
    }
    char buffer[SIZE * 100];
    clock_t start = clock();
    int k = 0;
    while ((k = read(fd, buffer, SIZE * 100)) == SIZE * 100)
    {
#pragma omp parallel for schedule(static)
        for (int i = 0; i < SIZE; i++)
        {
            sudoku s = {
                .col_usage = {0},
                .grid_usage = {0},
                .row_usage = {0}};
            from_string(&s, buffer + (i * 100 + 13));
            solve(&s);
        }
    }
    if (k != 0)
    {
        if (k % 100 != 0)
        {
            perror("The reading isn't complete");
            exit(1);
        }
        int len = k / 100;
#pragma omp parallel for
        for (int i = 0; i < len; i++)
        {
            sudoku s;
            from_string(&s, buffer + (i * 100 + 13));
            solve(&s);
        }
    }
    clock_t elasped = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
    printf("Time to compute: %ld\n", elasped);
}