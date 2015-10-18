all:createdata3 createdata6 createdata9
	./createdata3
	./createdata6
	./createdata9

createdata3:createdata3.c
	gcc -Wall -pedantic -ansi createdata3.c -o createdata3

createdata6:createdata6.c
	gcc -Wall -pedantic -ansi createdata6.c -o createdata6

createdata9:createdata9.c
	gcc -Wall -pedantic -ansi createdata9.c -o createdata9

data3:createdata3
	./createdata3

data6:createdata6
	./createdata6

data9:createdata9
	./createdata9

clean:
	rm  data3 data6 data9 createdata3 createdata6 createdata9
	
