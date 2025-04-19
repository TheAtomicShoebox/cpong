main: main.c main.h
	gcc -g -Wall main.c -o main -lncurses 

clean:
	rm -f main
