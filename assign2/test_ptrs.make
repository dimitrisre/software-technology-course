CFLAGS = -Wall -pedantic -ansi 
CC = gcc
test:			test.c mystring.h mystring_ptrs.c
			gcc  -Wall -pedantic -ansi test.c mystring_ptrs.c -o test
mystring_ptrs.c:	mystring.h

