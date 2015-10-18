CFLAGS= -Wall -pedantic -ansi
CC=gcc
CLEAN=rm -rf *.o

testsymtab: testsymtab.o symtablehash.o
	${CC} ${CFLAGS} testsymtab.o symtablehash.o -o testsymtab
	${CLEAN}

testsymtab.o: testsymtab.c
	${CC} ${CFLAGS} -c testsymtab.c

symtablehash.o: symtablehash.c
	${CC} ${CFLAGS} -c symtablehash.c

testsymtab.c: symtable.h logic.h


symtablehash.c: symtable.h logic.h

