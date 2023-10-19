

all: exec

exec: main.o grafo.o
	gcc -o exec main.o grafo.o -std=c++11

main.o:	main.cpp grafo.h
	gcc -o main.o main.cpp -c -W -Wall -ansi -pedantic

grafo.o: grafo.cpp grafo.h
	gcc -o grafo.o grafo.cpp -c -W -Wall -ansi -pedantic


clean:
	rm -rf *.o *~ exec