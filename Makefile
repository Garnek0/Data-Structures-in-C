all: build

SRC := $(shell find . -name '*.c')

.PHONY: build
build:
	gcc $(SRC) -O3 -o main -I.

.PHONY: run
run: build
	./main

.PHONY: clean
clean:
	rm -rf main.out
