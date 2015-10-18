libmymalloc.so: 	mymalloc.c mymalloc.h
			gcc -Wall -pedantic -ansi -G -o libmymalloc.so mymalloc.c	
	
