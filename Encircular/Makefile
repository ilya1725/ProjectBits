all:	encircular test
.PHONY : all

encircular:
	@echo "Building $@: "
	g++ -O0 -Wall -Wconversion -lstdc++ -std=c++17 -o encircular Encircular/Encircular.cpp

test:
	@echo "Test encircular"
	python test_encircular.py -e ./encircular
	python test_encircular.py -e ./encircular -i tests.txt

clean:
	rm -f encircular
	rm -f *.o
