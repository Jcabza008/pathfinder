CC = g++
CFLAGS = -g
INCLUDE = -I ./include

all: pathfinder mapgenerator

clean:
	rm -rf bin lib

bin/:
	mkdir -p bin

lib/:
	mkdir -p lib

pathfinder: bin/ lib/pathfinder.o
	$(CC) $(CFLAGS) $(INCLUDE) -o bin/pathfinder lib/pathfinder.o

mapgenerator: bin/ lib/mapgenerator.o
	$(CC) $(CFLAGS) $(INCLUDE) -o bin/mapgenerator lib/mapgenerator.o

lib/pathfinder.o: lib/
	$(CC) $(CFLAGS) $(INCLUDE) -c src/pathfinder/main.cpp -o lib/pathfinder.o

lib/graph.o: lib/
	$(CC) $(CFLAGS) $(INCLUDE) -c src/pathfinder/graph.cpp -o lib/graph.o

lib/mapgenerator.o: lib/
	$(CC) $(CFLAGS) $(INCLUDE) -c src/mapgenerator/main.cpp -o lib/mapgenerator.o


