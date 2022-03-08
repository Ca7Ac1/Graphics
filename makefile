show: compile
	./main.exe

compile: main.o window.o graphics.o renderer.o matrix.o script.o transform.o 
	g++ -std=c++11 -o main.exe main.o window.o graphics.o renderer.o script.o transform.o matrix.o

main.o: main.cpp window.hpp renderer.hpp script.hpp
	g++ -std=c++11 -c main.cpp 

window.o: window.cpp window.hpp
	g++ -std=c++11 -c window.cpp

graphics.o: graphics.cpp graphics.hpp matrix.hpp transform.hpp
	g++ -std=c++11 -c graphics.cpp

renderer.o: renderer.cpp renderer.hpp window.hpp graphics.hpp
	g++ -std=c++11 -c renderer.cpp

transform.o: transform.cpp transform.hpp graphics.hpp matrix.hpp
	g++ -std=c++11 -c transform.cpp

script.o: script.cpp script.hpp window.hpp renderer.hpp graphics.hpp transform.hpp
	g++ -std=c++11 -c script.cpp