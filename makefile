PORT ?= 8080

main: *.c *.h
	gcc -o main $^ -Wall -Wextra -pedantic -std=c99 -lm

.PHONY: run
run: main
	./main $(PORT)

.PHONY: memtest
memtest: main send_request.sh
	PORT=$(PORT) ./send_request.sh &
	valgrind --leak-check=full ./main $(PORT)
