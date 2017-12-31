CC=gcc
CFLAGS=-I.
TEST_DEPS = Test/Test.h
MAP_DEPS = Map/Map.h

%.o: %.c $(TEST_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.c $(MAP_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

map_test: Map/Map.o Test/Test.o Map/Test.o
	gcc -o mapTest Map/Map.o Test/Test.o Map/Test.o
	
clean:
	rm mapTest
	rm Map/*.o
	rm Test/*.o
	
