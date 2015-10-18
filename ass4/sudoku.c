#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "grid.h"



Grid_T sudoku_read(void){
	Grid_T *s=(Grid_T *)malloc(1*sizeof(Grid_T));
	int i=0,j=0,el;
	while((el=getchar())!=EOF)
	{
		if(el>='0' && el<='9'){
			grid_update_value(s, i, j, el-'0');
			j++;
		}
		else if(el=='\n'){
		    i++;
		    j=0;
		}
	}
	return *s;

}

void sudoku_print(FILE *s, Grid_T g)
{
	int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			fprintf(s,"%d ",grid_read_value(g, i, j));
		}
		fprintf(s,"\n");
	}
}

int sudoku_check_line(Grid_T g, int i, int j, int val)
{
	int k,sum=0;
	for(k=0;k<9;k++)
	{
		if(val!=-1)
		{
			if(grid_read_value(g,i,k)==val )
				return 1; // ara yparxei mesa sthn grammh h timh pou 8eloume na dwsoume
			//else 
			//	continue;
		}
		//if (grid_read_value(g,i,j)==grid_read_value(g,i,k)&& (k!=j) )
		//	return 1; //an yparxei sth grammh 3ana to idio stoixeio
		sum=sum+grid_read_value(g,i,k);
	}
	if(sum!=45&& val==-1)
		return 1; //dld problhma sthn grammh
	return 0;
}

int sudoku_check_col(Grid_T g, int i, int j, int val)
{       int k,sum=0;
        for(k=0;k<9;k++)
        {
		if(val!=-1)
                { 
                        if(grid_read_value(g,k,j)==val)
                                return 1; // ara yparxei mesa sthn grammh h timh
                        //else 
                        //        continue;
                }

               // if (grid_read_value(g,i,j)==grid_read_value(g,k,j)&& (k!=i))
                 //       return 1; //an yparxei sth grammh 3ana to idio stoixeio
		sum=sum+grid_read_value(g,k,j);
        }
	if(sum!=45&& val==-1)
		return 1;
        return 0;
}

int which_grid(Grid_T g,int j)
{
	if(j<3)
		return 0; // anhkei sta grid tis prwths sthlhs
	else if(j<6)
		return 3; //anhkei sta grid ths 2 sthlhs
	else
		return 6; // anhkei sta grid ths 3 sthlhs
}

int sudoku_check_grid(Grid_T g, int i, int j,int val)
{
	int arxh_sthlhs=which_grid(g,j);
	int arxh_grammhs=which_grid(g,i);
	int row,col,sum=0;

       	for(row=arxh_grammhs;row<arxh_grammhs+3;row++)
       	{
		for(col=arxh_sthlhs;col<arxh_sthlhs+3;col++)// me ayto tn tropo briskw to stwsto grip analoga me thn sthlh
		{
               		if(val!=-1)
               		{
                       		if(grid_read_value(g,row,col)==val)
                               		return 1; // ara yparxei
                       	//	else
                          //     		continue;
               		}
        	       // if (grid_read_value(g,i,j)==grid_read_value(g,row,col)&& (row!=i&& col!=j))
	                 //       return 1; //an yparxei 
			sum=sum+grid_read_value(g,row,col);
		}
       	}

	if(sum!=45 && val==-1)
		return 1;

        return 0;
}

void sudoku_print_errors(Grid_T g)
{
	int i,j,row,col,grid;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			row=sudoku_check_line(g,i,j,-1);
			if(row==1)
				printf("error: yparxei 3ana o ari8mos %d sthn grammh %d\n",grid_read_value(g,i,j),i);
			col=sudoku_check_col(g, i,j,-1);
			if(col==1)
				printf("error: yparxei 3ana o ari8mos %d sthn sthlh %d\n",grid_read_value(g,i,j),j);
			grid=sudoku_check_grid( g, i,j,-1);
			if(grid==1)
				printf("error: yparxei 3ana o ari8mos %d sto grid pou anhkei\n", grid_read_value(g,i,j));

		}
	}
}
int sudoku_solution_is_unique(Grid_T g){
	return grid_read_unique(g);
}

int sudoku_is_correct(Grid_T g)
{
	int i,j,row,col,grid;
	for(i=0;i<9;i++)
        {
              for(j=0;j<9;j++)    // ebgala ayth th for kai to grod apo ta sxolia...
              {
                        row=sudoku_check_line(g,i,j,-1);
                        if(row==1)
                                return 0;
                        col=sudoku_check_col(g, i,j,-1);
                        if(col==1)
                                return 0;
                        grid=sudoku_check_grid( g, i,j,-1);
                        if(grid==1)
                               return 0;


        	}
	}
	return 1; // einai olo swsto to puzlle

}




/*static*/void sudoku_init_choices(Grid_T *g){
	int i,j,k;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(grid_read_value( *g, i,j)==0)
			{
				grid_set_count(g, i, j);
				for(k=1;k<10;k++)
				{
					if( sudoku_check_line(*g, i, j,k)==1)
					{
						grid_remove_choice(g, i, j,k);
						continue;
					}
					if( sudoku_check_col(*g, i, j,k)==1)
                                        {
                                                grid_remove_choice(g, i, j,k);
                                                continue;
                                        }
					if(sudoku_check_grid(*g, i, j,k)==1)
					{
						grid_remove_choice(g, i, j,k);
						continue;
					}

					grid_set_choice(g, i, j,k);
				}
			}
			else 
				grid_clear_count(g,i,j);

		}
	}
}


void print_choices(Grid_T g){
	int i,j,k;

	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			printf("(%d,%d)=%d [",i,j,g.elts[i][j].choices.count);
			for(k=1; k<10; k++){
				printf("%d,",g.elts[i][j].choices.num[k]);
			}
			printf("]\n");
		}
	}

}
/*static */int sudoku_try_next(Grid_T g, int *row, int *col)
{
	int i,j,found=0, ran=0,k,counter=-1;

	
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(grid_read_value( g, i, j)==0 && grid_read_count(g,i,j)==1)
			{
				*row=i;
				*col=j;
				found=1;
				break;
			}
		}
		if(found==1)
			break;
	}

	if(found == 0)
	{
		for(i=0;i<9;i++)
 	       {
        	        for(j=0;j<9;j++)
                	{
                        	if(grid_read_value( g, i, j)==0)
                        	{
                                	*row=i;
                                	*col=j;
                                	found=1;
                                	break;
                        	}
                	}
                	if(found==1)
                        	break;
        	}

	}
	
	if(found == 0){
		return -1;
	}

	if(grid_read_value(g,*row,*col) != 0)
		return -1;

	j = grid_read_count( g, *row, *col);
	
	if(j == 0)
		return -1;

	ran=rand()%j;
	for(k=1;k<10;k++)
	{
		if(grid_choice_is_valid( g, *row, *col, k)==1)
		{
			counter++;
			if(counter==ran)
			{
				//printf("%d,%d=%d\n",*row, *col,k);
				return k;
			}
		}
	}
	return -1;

}

/*static*/ int sudoku_update_choice(Grid_T *g, int i, int j, int n)
{
	int epiloges=grid_read_count(*g, i, j);
	grid_remove_choice(g, i, j, n);
	return epiloges;

}

void sudoku_eliminate_choice(Grid_T *g, int r, int c, int n)
{
	int i,j,k,l;
	for(i=0;i<9;i++) // elegxw thn grammh
	{
		if(grid_choice_is_valid(*g,i,c,n)){
                        grid_remove_choice(g,i,c,n);
                }

	}
	for(j=0;j<9;j++) // elegxw thn sthlh
	{
		if(grid_choice_is_valid(*g,r,j,n)){
                        grid_remove_choice(g,r,j,n);
                }

	}
	k=which_grid(*g,r);
	l=which_grid(*g,c);
	for(i=k;i<k+3;i++)
	{
		for(j=l;j<l+3;j++)
		{
			if(grid_choice_is_valid(*g,i,j,n)){
                                grid_remove_choice(g,i,j,n);
                        }
	
		}
	}

}


Grid_T sudoku_solve(Grid_T g)
{
	int ch=0,i,j;
	Grid_T tmp;
	int unique=1;
	grid_clear_unique(&g);
	if(sudoku_is_correct(g) == 1)
		return g;
	
	//if(i>8 || j>8)return g;
	
	sudoku_init_choices(&g);
		while((ch=sudoku_try_next(g,&i,&j))!=-1)
			{
				if(grid_read_count(g,i,j)==1)
				{
					sudoku_update_choice(&g,i, j,ch);
					sudoku_eliminate_choice(&g,i,j,ch);
					grid_update_value(&g,i,j,ch);

				}
				else
				{	grid_clear_unique(&g);
					tmp=g;
					grid_clear_unique(&tmp);
					unique = 0;
					sudoku_update_choice(&tmp,i, j,ch);
					sudoku_eliminate_choice(&tmp,i,j,ch);
					grid_update_value(&tmp,i,j,ch);
					tmp=sudoku_solve(tmp);

					if(sudoku_is_correct(tmp)==1){
						return tmp;
					}
					else{
						grid_remove_choice(&g, i, j, ch);
					}

				}

			}
	if(unique == 1)
		grid_set_unique(&g);
	return g;
}

static Grid_T sudoku_generate_complete(void)
{
	int i,j,k,ch;
	Grid_T *g=(Grid_T*)malloc(1*sizeof(Grid_T));
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			grid_update_value(g,i, j,0);
		}
	}
	

//	sudoku_init_choices(g);

	*g = sudoku_solve(*g);
		
	return *g;
}

Grid_T sudoku_generate(int nelts, int unique){

	Grid_T g = sudoku_generate_complete();
	int i=0,c,r;
	
	for(i=0;i <((9*9)-nelts); i++){
		do{
			r = rand()%9;
			c = rand()%9;
		}while(grid_read_value(g,r,c)==0);

		grid_update_value(&g,r,c,0);
	}
	
	return g;

}
