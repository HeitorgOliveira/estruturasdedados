run: all
	./main.exe < ../casos_teste/8.in

all: clean ls avl conjunto main
	gcc -o main.exe ls.o avl.o conjunto.o main.o

ls:
	gcc -c ls.c

avl: 
	gcc -c avl.c

conjunto:
	gcc -c conjunto.c

main:
	gcc -c main.c

clean:
	rm *.o main.exe