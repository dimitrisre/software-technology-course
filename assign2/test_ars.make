CFLAGS = -Wall -pedantic -ansi
CC = gcc 

test:			test.c mystring.h mystring_ars.c
			gcc -Wall -pedantic -ansi  test.c mystring_ars.c -o test
mystring_ars.c:	mystring.h

