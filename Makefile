CC=gcc
CFLAGS=-I.
TEST_DEPS = Test/Test.h
MAP_DEPS = Map/Map.h

SHELL:=/bin/bash

%.o: %.c $(TEST_DEPS)
	$(CC) -Werror -c -o $@ $< $(CFLAGS)

%.o: %.c $(MAP_DEPS)
	$(CC) -Werror -c -o $@ $< $(CFLAGS)

map_test: Map/Map.o Test/Test.o Map/Test.o
	gcc -Werror -o mapTest Map/Map.o Test/Test.o Map/Test.o
	
clean:
	rm mapTest
	rm Map/*.o
	rm Test/*.o
	