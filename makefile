run: all
	./main.exe

all:clean ls avl conjunto main
	gcc -o main.exe rb.o avl.o conjunto.o main.o

ls:
	gcc -c rb.c

avl: 
	gcc -c ls.c

conjunto:
	gcc -c conjunto.c

main:
	gcc -c main.c

clean:
	rm *.o main.exe