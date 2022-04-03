show: compile
	./main.exe

gallery: compile_gallery
	./gallery.exe

compile_gallery: gallery.o window.o graphics.o renderer.o matrix.o script.o transform.o graphics3d.o
	g++ -std=c++11 -o gallery.exe gallery.o window.o graphics.o renderer.o script.o transform.o matrix.o graphics3d.o

compile: main.o window.o graphics.o renderer.o matrix.o script.o transform.o graphics3d.o
	g++ -std=c++11 -o main.exe main.o window.o graphics.o renderer.o script.o transform.o matrix.o graphics3d.o

gallery.o: gallery.cpp window.hpp renderer.hpp script.hpp
	g++ -std=c++11 -c gallery.cpp 

main.o: main.cpp window.hpp renderer.hpp script.hpp
	g++ -std=c++11 -c main.cpp 

window.o: window.cpp window.hpp
	g++ -std=c++11 -c window.cpp

graphics.o: graphics.cpp graphics.hpp matrix.hpp transform.hpp
	g++ -std=c++11 -c graphics.cpp

graphics3d.o: graphics3d.cpp graphics3d.hpp graphics.hpp matrix.hpp transform.hpp
	g++ -std=c++11 -c graphics3d.cpp

renderer.o: renderer.cpp renderer.hpp window.hpp graphics.hpp graphics3d.hpp
	g++ -std=c++11 -c renderer.cpp

transform.o: transform.cpp transform.hpp graphics.hpp matrix.hpp
	g++ -std=c++11 -c transform.cpp

script.o: script.cpp script.hpp window.hpp renderer.hpp graphics.hpp transform.hpp
	g++ -std=c++11 -c script.cpp

matrix.o: matrix.cpp matrix.hpp
	g++ -std=c++11 -c matrix.cpp