CFLAGS= -Wall -pedantic -ansi 
CC= gcc

testar:  libmymalloc.so test_darray.o darray.o
 	${CC} ${CFLAGS} -L./ -R./ test_darray.o darray.o -lmymalloc -o testar
libmymalloc.so: mymalloc.c
	${CC} ${CFLAGS} -G mymalloc.c -o libmymalloc.so

test_darray.o: test_darray.c
	${CC} ${CFLAGS} -c test_darray.c 

test_darray.c: darray.h

darray.o:  darray.c 
	${CC} ${CFLAGS} -c darray.c

darray.c:  darray.h malloc.h
