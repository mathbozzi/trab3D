all:
	g++ -std=c++11 main.cpp tinyxml2.cpp Arena.cpp Circle.cpp EstruturasBasicas.cpp Rect.cpp input.cpp Helicoptero.cpp Tiro.cpp imageloader.cpp -o trabalhocg -lGL -lGLU -lglut 

valgrind:
	g++ -g -std=c++11 main.cpp tinyxml2.cpp Arena.cpp Circle.cpp EstruturasBasicas.cpp Rect.cpp input.cpp Helicoptero.cpp Tiro.cpp imageloader.cpp -o trabalhocg -lGL -lGLU -lglut 

clean:
	rm -rf trabalhocg
