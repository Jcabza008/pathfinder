CC = g++
INCLUDEFLAG = -I include
LIBFLAG = -L lib
CFLAGS = -g $(LIBSFLAG) $(INCLUDEFLAG)

LIBS = lib/graph.o lib/util.o

GTEST = gtest-1.7.0/include
LIBGTEST = /usr/lib/libgtest_main.a /usr/lib/libgtest.a

run_pathfinder: pathfinder
	./bin/pathfinder

run_mapgenerator: mapgenerator
	./bin/mapgenerator

run_tests: tests
	./bin/tests

all: pathfinder mapgenerator tests

clean:
	rm -rf bin lib

bin/:
	mkdir -p bin

lib/:
	mkdir -p lib

pathfinder: bin/ lib/pathfinder.o $(LIBS)
	$(CC) $(CFLAGS) -o bin/pathfinder lib/pathfinder.o

mapgenerator: bin/ lib/mapgenerator.o $(LIBS)
	$(CC) $(CFLAGS) -o bin/mapgenerator lib/mapgenerator.o

tests: bin/ lib/tests.o $(LIBS)
	$(CC) $(CFLAGS) -o bin/tests lib/tests.o $(LIBGTEST) $(LIBS) -lpthread

# Main Libs
lib/pathfinder.o: lib/ $(LIBS)
	$(CC) $(CFLAGS) -c src/pathfinder.cpp -o lib/pathfinder.o

lib/mapgenerator.o: lib/ $(LIBS)
	$(CC) $(CFLAGS) -c src/mapgenerator.cpp -o lib/mapgenerator.o

lib/tests.o: lib/ $(LIBS)
	$(CC) $(CFLAGS) -c tests/tests.cpp -lpthread -o lib/tests.o

# Libs
lib/graph.o: lib/
	$(CC) $(CFLAGS) -c src/graph.cpp -o lib/graph.o

lib/util.o: lib/
	$(CC) $(CFLAGS) -c src/util.cpp -o lib/util.o