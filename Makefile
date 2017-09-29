FLAGS= -g -Wall -std=c99

all: lab_1

lab_1:  grafo.o lab_1.o lista.o
	gcc $(FLAGS) lista.o grafo.o lab_1.o -o lab_1

lab_1.o: lab_1.c lab_1.h
	gcc $(FLAGS) -c lab_1.c -o lab_1.o

grafo.o: grafo.h grafo.c
	gcc $(FLAGS) -c grafo.c -o grafo.o

lista.o: lista.h lista.c
	gcc $(FLAGS) -c lista.c -o lista.o

clean:
	rm -f *.o lab_1.exe lab_1
