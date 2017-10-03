
bin/main: bin/main.o
	g++ -I -g -o bin/main bin/main.o -std=c++11 -Wall -pedantic -lncursesw

bin/main.o: src/main.cpp
	mkdir -p bin
	g++ -I -g -c -o bin/main.o src/main.cpp -lncursesw