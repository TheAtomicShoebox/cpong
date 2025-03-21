main: main.c main.h
	gcc main.c -o main -lncurses 

clean:
	rm -f main
