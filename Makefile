sudoku.o:sudoku.c
	gcc -c sudoku.c -o sudoku.o
main.o:main.c
	gcc -c main.c -o main.o

my_program:main.o sudoku.o
	gcc -o my_program main.o sudoku.o
run:my_program
	./my_program
clean:
	rm *.o