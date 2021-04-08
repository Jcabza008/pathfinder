CC = g++
CFLAGS = -g

all: pathfinder mapgenerator

clean:
	rm -rf bin obj

bin/:
	mkdir -p bin

obj/:
	mkdir -p obj

pathfinder: bin/ obj/ obj/pathfinder.o
	$(CC) $(CFLAGS) -o bin/pathfinder obj/pathfinder.o

obj/pathfinder.o:
	$(CC) $(CFLAGS) -c src/pathfinder/main.cpp -o obj/pathfinder.o

mapgenerator: bin/ obj/ obj/mapgenerator.o
	$(CC) $(CFLAGS) -o bin/mapgenerator obj/mapgenerator.o

obj/mapgenerator.o:
	$(CC) $(CFLAGS) -c src/mapgenerator/main.cpp -o obj/mapgenerator.o