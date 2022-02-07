all: compile
	./main.exe

compile: main.o window.o 
	g++ -o main.exe main.o window.o

main.o: main.cpp window.hpp
	g++ -c main.cpp 

window.o: window.cpp window.hpp
	g++ -c window.cpp