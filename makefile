CC = g++
CFLAGS = -std=c++11 -Wall -g

all: exec

exec: main.o grafo.o
	$(CC) $(CFLAGS) main.o grafo.o -o exec

main.o:	main.cpp grafo.h
	$(CC) $(CFLAGS) main.cpp -o main.o -c

grafo.o: grafo.cpp grafo.h aresta.h
	$(CC) $(CFLAGS) grafo.cpp -o grafo.o -c

run:
	./exec

clean:
	rm -rf *.o *~ exec