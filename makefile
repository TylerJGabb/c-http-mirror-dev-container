main: *.c
	gcc -o main main.c -Wall -Wextra -pedantic -std=c99 -lm

.PHONY: run
run: main
	./main

.PHONY: memtest
memtest: main
	valgrind --leak-check=full ./main abcdefghijklmnopqrstuvwxyz