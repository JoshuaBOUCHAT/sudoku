sudoku.o:sudoku.c
	gcc -O3 -Wall -Wextra -Werror -pedantic -c sudoku.c -o sudoku.o
main.o:main.c
	gcc -O3 -Wall -Wextra -Werror -pedantic -c main.c -o main.o

my_program:main.o sudoku.o
	gcc -O3 -Wall -Wextra -Werror -pedantic -o my_program main.o sudoku.o
run:my_program
	./my_program
clean:
	rm *.o