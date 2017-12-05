SOURCES = src/TypestNetworking.cpp src/main.cpp 

bin/typest.out: bin/typest.o bin/TypestNetworking.o
	g++ -I -g -o bin/typest.out bin/typest.o bin/TypestNetworking.o -std=c++11 -Wall -pedantic -lncursesw -ltinfo -D_GLIBCXX_USE_CXX11_ABI=0

bin/typest.o: $(SOURCES)
	mkdir -p bin
	g++ -I -g -c -o bin/typest.o src/main.cpp -std=c++11 -lncursesw -ltinfo

bin/TypestNetworking.o: $(SOURCES)
	g++ -I -g -c -o bin/TypestNetworking.o src/TypestNetworking.cpp -std=c++11 -lncursesw -ltinfo