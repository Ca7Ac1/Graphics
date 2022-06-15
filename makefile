show: compile
	./mdl.exe gallery.mdl ; python3 convert.py animate key

gallery: compile
	./mdl.exe gallery.mdl ; python3 convert.py animate key

clean: 
	rm -f *.o ; rm -f *.exe ; rm -f *.ppm ; rm -f *.png ; rm -f anim/*.ppm ; rm -f anim/*.png ; rm -f *.gif

flex:
	cd mdl ; flex -I mdl.l

bison:
	cd mdl ; bison -d -y mdl.y

compile: y.tab.o symtab.o window.o graphics.o renderer.o matrix.o script.o transform.o graphics3d.o context.o lighting.o
	g++ -std=c++11 -o mdl.exe y.tab.o symtab.o window.o graphics.o renderer.o script.o transform.o matrix.o graphics3d.o context.o lighting.o

y.tab.o: mdl/y.tab.cpp mdl/y.tab.hpp mdl/parser.hpp mdl/symtab.hpp mdl/symtab.cpp mdl/lex.yy.cc 
	g++ -std=c++11 -c mdl/y.tab.cpp

symtab.o: mdl/symtab.cpp matrix.hpp mdl/parser.hpp mdl/symtab.hpp mdl/symtab.cpp mdl/lex.yy.cc 
	g++ -std=c++11 -c mdl/symtab.cpp

window.o: window.cpp window.hpp
	g++ -std=c++11 -c window.cpp

graphics.o: graphics.cpp graphics.hpp matrix.hpp transform.hpp
	g++ -std=c++11 -c graphics.cpp

graphics3d.o: graphics3d.cpp graphics3d.hpp graphics.hpp matrix.hpp transform.hpp
	g++ -std=c++11 -c graphics3d.cpp

renderer.o: renderer.cpp renderer.hpp window.hpp graphics.hpp graphics3d.hpp context.hpp lighting.hpp
	g++ -std=c++11 -c renderer.cpp

context.o: context.cpp context.hpp transform.hpp graphics.hpp graphics3d.hpp
	g++ -std=c++11 -c context.cpp

transform.o: transform.cpp transform.hpp graphics.hpp matrix.hpp
	g++ -std=c++11 -c transform.cpp

script.o: script.cpp script.hpp window.hpp renderer.hpp graphics.hpp transform.hpp
	g++ -std=c++11 -c script.cpp

matrix.o: matrix.cpp matrix.hpp
	g++ -std=c++11 -c matrix.cpp

lighting.o: lighting.cpp lighting.hpp window.hpp matrix.hpp graphics3d.hpp
	g++ -std=c++11 -c lighting.cpp