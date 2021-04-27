all:
	g++ -std=c++11 main.cpp tinyxml2.cpp jogo.cpp circulo.cpp utils.cpp retangulo.cpp input.cpp lutador.cpp imageloader.cpp -o trabalhocg -lGL -lGLU -lglut 

valgrind:
	g++ -g -std=c++11 main.cpp tinyxml2.cpp jogo.cpp circulo.cpp utils.cpp retangulo.cpp input.cpp lutador.cpp imageloader.cpp -o trabalhocg -lGL -lGLU -lglut 

clean:
	rm -rf trabalhocg
