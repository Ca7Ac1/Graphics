show: compile
	./main.exe ; display main.ppm

compile: main.o window.o graphics.o renderer.o 
	g++ -std=c++11 -o main.exe main.o window.o graphics.o renderer.o 

main.o: main.cpp window.hpp
	g++ -std=c++11 -c main.cpp 

window.o: window.cpp window.hpp
	g++ -std=c++11 -c window.cpp

graphics.o: graphics.cpp renderer.hpp
	g++ -std=c++11 -c graphics.cpp

renderer.o: renderer.cpp renderer.hpp window.hpp graphics.hpp
	g++ -std=c++11 -c renderer.cpp
