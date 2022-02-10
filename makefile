all: compile
	./main.exe

compile: main.o window.o 
	g++ -std=c++11 -o main.exe main.o window.o

main.o: main.cpp window.hpp
	g++ -std=c++11 -c main.cpp 

window.o: window.cpp window.hpp
	g++ -std=c++11 -c window.cpp