all:	encircular test
.PHONY : all

encircular:
	@echo "Building $@: "
	g++ -O0 -Wall -Wconversion -lstdc++ -std=c++17 -o Encircular Encircular/Encircular.cpp

test:
	@echo "Test"
	test_encircular.py -e Encircular
	test_encircular.py -e Encircular -i tests.txt

clean:
	rm -f Encircular
	rm -f *.o
