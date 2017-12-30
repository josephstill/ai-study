 
CC=gcc
CFLAGS=-I.
MAP_DEPS = Map/Map.h

%.o: %.c $(MAP_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

map_test: Map/Map.o Map/Test.o
	gcc -o test Map/Map.o Map/Test.o
	
clean:
	rm test
	rm Map/*.o
	
