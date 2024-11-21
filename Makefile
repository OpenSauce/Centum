compile:
	gcc $(wildcard *.c) $(wildcard */*.c) -o centum

play:
	./centum

.PHONY: compile play