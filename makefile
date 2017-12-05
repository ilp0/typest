SOURCES = src/TypestNetworking.cpp src/main.cpp 

bin/main.sh: bin/main.o bin/TypestNetworking.o
	g++ -I -g -o bin/main.sh bin/main.o bin/TypestNetworking.o -std=c++11 -Wall -pedantic -lncursesw -ltinfo -D_GLIBCXX_USE_CXX11_ABI=0

bin/main.o: $(SOURCES)
	mkdir -p bin
	g++ -I -g -c -o bin/main.o src/main.cpp -std=c++11 -lncursesw -ltinfo

bin/TypestNetworking.o: $(SOURCES)
	g++ -I -g -c -o bin/TypestNetworking.o src/TypestNetworking.cpp -std=c++11 -lncursesw -ltinfo