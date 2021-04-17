CC = g++
INCLUDEFLAG = -I include
LIBSFLAG = -L lib
CFLAGS = -g -Wall -std=c++14 $(LIBSFLAG) $(INCLUDEFLAG)

CORELIBS = lib/log.o lib/graph.o lib/util.o lib/priority_queue.o \
		lib/algorithms.o lib/color.o
VIEWLIBS = lib/app_window.o lib/button.o lib/component_base.o lib/composite_component.o \
		lib/window_base.o lib/texture_provider.o lib/map_view.o lib/simple_views.o

SFMLFLAGS = `pkg-config sfml-all --cflags --libs`
GTESTFLAGS = `pkg-config gtest gmock --cflags --libs`

CPPCOREGUIDELINES = 'cppcoreguidelines-avoid-goto,	 						\
				cppcoreguidelines-avoid-non-const-global-variables,	 		\
				cppcoreguidelines-init-variables,	                    	\
				cppcoreguidelines-interfaces-global-init,	            	\
				cppcoreguidelines-narrowing-conversions,                	\
				cppcoreguidelines-no-malloc,                            	\
				cppcoreguidelines-owning-memory,                        	\
				cppcoreguidelines-prefer-member-initializer,				\
				cppcoreguidelines-pro-bounds-constant-array-index,	 		\
				cppcoreguidelines-pro-type-const-cast,	  					\
				cppcoreguidelines-pro-type-cstyle-cast,						\
				cppcoreguidelines-pro-type-member-init,						\
				cppcoreguidelines-pro-type-reinterpret-cast,  				\
				cppcoreguidelines-pro-type-static-cast-downcast,			\
				cppcoreguidelines-pro-type-vararg,	  						\
				cppcoreguidelines-slicing,	  								\
				cppcoreguidelines-c-copy-assignment-signature,				\
				cppcoreguidelines-explicit-virtual-functions'

# TODO Fix issues with this guidelines
DISABLEDCPPCOREGUIDELINES = 'cppcoreguidelines-pro-type-union-access,  		\
				cppcoreguidelines-avoid-magic-numbers,						\
				cppcoreguidelines-avoid-c-arrays,							\
				cppcoreguidelines-pro-bounds-array-to-pointer-decay, 		\
				cppcoreguidelines-macro-usage,								\
				cppcoreguidelines-non-private-member-variables-in-classes,  \
				cppcoreguidelines-pro-bounds-pointer-arithmetic,			\
				cppcoreguidelines-special-member-functions'

run_clang_tidy:
	clang-tidy -checks=$(CPPCOREGUIDELINES) --warnings-as-errors=* -header-filter=.* src/* -- $(CFLAGS)

run_pathfinder: pathfinder
	./bin/pathfinder

run_tests: tests
	./bin/tests

all: pathfinder tests

clean:
	rm -rf bin lib

bin/:
	mkdir -p bin

lib/:
	mkdir -p lib

pathfinder: bin/ lib/main.o $(CORELIBS) $(VIEWLIBS)
	$(CC) $(CFLAGS) -o bin/pathfinder lib/main.o $(CORELIBS) $(VIEWLIBS) $(SFMLFLAGS) -lpthread

tests: bin/ lib/tests.o $(CORELIBS)
	$(CC) $(CFLAGS) -o bin/tests lib/tests.o $(CORELIBS) $(SFMLFLAGS) $(GTESTFLAGS) -lpthread

# Main Libs
lib/main.o: lib/ $(LIBS)
	$(CC) $(CFLAGS) -c src/main.cpp -o lib/main.o $(SFMLFLAGS)

lib/tests.o: lib/ $(LIBS)
	$(CC) $(CFLAGS) -c tests/tests.cpp -lpthread -o lib/tests.o

# Libs
lib/log.o: lib/
	$(CC) $(CFLAGS) -c src/log.cpp -o lib/log.o

lib/graph.o: lib/
	$(CC) $(CFLAGS) -c src/graph.cpp -o lib/graph.o

lib/priority_queue.o: lib/
	$(CC) $(CFLAGS) -c src/priority_queue.cpp -o lib/priority_queue.o

lib/algorithms.o: lib/
	$(CC) $(CFLAGS) -c src/algorithms.cpp -o lib/algorithms.o

lib/util.o: lib/
	$(CC) $(CFLAGS) -c src/util.cpp -o lib/util.o

lib/color.o: lib/
	$(CC) $(CFLAGS) -c src/color.cpp -o lib/color.o

# View Libs
lib/texture_provider.o: lib/
	$(CC) $(CFLAGS) -c src/texture_provider.cpp -o lib/texture_provider.o $(SFMLFLAGS)

lib/simple_views.o: lib/
	$(CC) $(CFLAGS) -c src/simple_views.cpp -o lib/simple_views.o $(SFMLFLAGS)

lib/button.o: lib/
	$(CC) $(CFLAGS) -c src/button.cpp -o lib/button.o $(SFMLFLAGS)

lib/component_base.o: lib/
	$(CC) $(CFLAGS) -c src/component_base.cpp -o lib/component_base.o $(SFMLFLAGS)

lib/composite_component.o: lib/
	$(CC) $(CFLAGS) -c src/composite_component.cpp -o lib/composite_component.o $(SFMLFLAGS)

lib/map_view.o: lib/
	$(CC) $(CFLAGS) -c src/map_view.cpp -o lib/map_view.o $(SFMLFLAGS)

lib/window_base.o: lib/
	$(CC) $(CFLAGS) -c src/window_base.cpp -o lib/window_base.o $(SFMLFLAGS)

lib/app_window.o: lib/
	$(CC) $(CFLAGS) -c src/app_window.cpp -o lib/app_window.o $(SFMLFLAGS)
