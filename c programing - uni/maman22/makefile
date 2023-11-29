makecomp: complex.o mycomp.o
	gcc -ansi -Wall -g mycomp.o complex.o -o makecomp -lm
complex.o: complex.c complex.h
	gcc -c -ansi -Wall complex.c -o complex.o -lm
mycomp.o: mycomp.c complex.h
	gcc -c -ansi -Wall mycomp.c -o mycomp.o -lm
