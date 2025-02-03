CFLAGS = -fopenmp -O3 -Wall -Wextra -Werror -pedantic

my_program:build build/main.o build/sudoku.o
	gcc $(CFLAGS) -o my_program build/main.o build/sudoku.o
build/sudoku.o:build sudoku.c
	gcc $(CFLAGS) -c sudoku.c -o build/sudoku.o
build/main.o:build main.c
	gcc $(CFLAGS) -c main.c -o build/main.o

build:
	mkdir build
run:my_program
	./my_program
clean:
	rm -rf build/ && rm my_program 