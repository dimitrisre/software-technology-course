CFLAGS= -Wall -pedantic -ansi
CC=gcc
CLEAN=rm -rf *.o

testsymtab: testsymtab.o symtablelist.o
	${CC} ${CFLAGS} testsymtab.o symtablelist.o -o testsymtab
	${CLEAN}

testsymtab.o: testsymtab.c
	${CC} ${CFLAGS} -c testsymtab.c

symtablelist.o: symtablelist.c
	${CC} ${CFLAGS} -c symtablelist.c

testsymtab.c: symtable.h logic.h


symtablelist.c: symtable.h logic.h



