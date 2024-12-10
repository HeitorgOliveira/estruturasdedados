run: all
	./main.exe

all:clean rb avl conjunto main
	gcc -o main.exe rb.o avl.o conjunto.o main.o

rb:
	gcc -c rb.c

avl: 
	gcc -c avl.c

conjunto:
	gcc -c conjunto.c

main:
	gcc -c main.c

clean:
	rm *.o main.exe