sudoku: sudoku.o main.o grid.o
	gcc sudoku.o main.o grid.o -o sudoku

sudoku.o: sudoku.c 
	gcc -c sudoku.c
 
main.o: main.c
	gcc -c main.c

grid.o: grid.c
	gcc -c grid.c

clean:
	rm *.o
