
all: clean
	gcc -o main main.c rsengine/loop.c

run: all
	./main

clean:
	rm -f main
