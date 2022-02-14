show: compile
	./main.exe ; magick display main.ppm

compile: main.o window.o renderer.o
	g++ -std=c++11 -o main.exe main.o window.o renderer.o

main.o: main.cpp window.hpp
	g++ -std=c++11 -c main.cpp 

window.o: window.cpp window.hpp
	g++ -std=c++11 -c window.cpp

renderer.o: renderer.cpp renderer.hpp window.hpp	
	g++ -std=c++11 -c renderer.cpp