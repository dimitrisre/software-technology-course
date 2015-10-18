#include <stdio.h>
#include <unistd.h>
#include"sudoku.h"
#include<string.h>

void sudoku_init_choices(Grid_T *g);
//void print_choices(Grid_T g);
//int sudoku_try_next(Grid_T g, int *row, int *col);
//void  sudoku_print_errors(Grid_T g);
Grid_T sudoku_generate_complete(void);

int main(int argc,char **argv)
{
	int i=0,j=0,nelts;
	
	srand(getpid());
	Grid_T g,l;

	if(argc == 1){
		g = sudoku_read();
		
		sudoku_print(stderr,g);
		l = sudoku_solve(g);
		fprintf(stderr,"<<<<<<<lysh>>>>>>>\n");
		sudoku_print(stderr,l);
		if(sudoku_solution_is_unique(l) == 1){
			printf("Exei monadikh lysh\n");
		}
		else{
			printf("Den exei monadikh lysh\n");
		}
	}
	if(argc > 1){
		if(strcmp(argv[1],"-c") == 0){
			g = sudoku_read();
		
			sudoku_print(stderr,g);
			if(sudoku_is_correct(g) == 1){
				printf("To puzzle einai swsto\n");
			}
			else{
				sudoku_print_errors(g);
			}
			return 0;
		}

		if(strcmp(argv[1],"-g") == 0){
			nelts = atoi(argv[2]);
			if(argc == 4){
				if(strcmp(argv[3],"-u") == 0){
					g = sudoku_generate(nelts,1);
					sudoku_print(stdout,g);
					return 0;
				}
			}
			g = sudoku_generate(nelts,0);
			sudoku_print(stdout,g);
		}
	}
	
	return 0;
}
