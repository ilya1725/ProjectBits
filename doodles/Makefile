all:	doodles ex2 ex3 memgoble file-search path
.PHONY : all

doodles:
	@echo "Building $@: general assemblage of code tests"
	g++ -lstdc++ -pthread -std=c++17 -o doodles src/doodles.cpp src/MapCheck.cpp

ex2:
	@echo "Building $@: "
	g++ -O3 -Wall -Wconversion -lstdc++ -pthread -std=c++17 -o ex2 src/ex2.cpp

ex3:
	@echo "Building $@: "
	g++ -O0 -Wall -Wconversion -lstdc++ -pthread -std=c++17 -o ex3 src/ex3.cpp

memgoble:
	@echo "Building $@: application that continuously allocates memory"
	g++ -Wall -Wconversion -lstdc++ -pthread -std=c++17 -o memgoble src/memgoble.cpp

file-search:
	@echo "Building $@: "
	g++ -Wall -Wconversion -lstdc++ -pthread -std=c++17 -o file-search src/file-search.cpp

path:
	@echo "Building $@: "
	g++ -Wall -Wconversion -lstdc++ -pthread -std=c++17 -o obstacle-path src/obstacle-path.cpp

clean:
	rm -f memgoble
	rm -f ex2
	rm -f ex3
	rm -f doodles
	rm -f file-search
	rm -f obstacle-path
