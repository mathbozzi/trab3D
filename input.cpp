// #include "input.h"

// using namespace std;
// using namespace tinyxml2;

// INPUT::INPUT(const string path)
// {
//     // carrega o SVG
//     XMLError error = this->input.LoadFile(path.c_str());

//     // verifica se houve erro
// 	this->isLoaded = (error == 0);
// }

// Arena INPUT::getArena()
// {
//     Arena arena;
//     float velocidadeLutador = 0.2;
//     float velocidadeOponente = 0.1;

//     // declara os elementos da arena
//     Rect mapa;
//     //Rect postoAbastecimento;
//     Circle areaJogador;
//     Circle areaOponente;
//     //vector<Circle> objetosResgate;

//     // pega os 'rect'
//     vector<Rect> rects = this->getRects();
//     for (Rect r : rects) {
//         arena.mapaCorID[r.id] = r.cor;
//         if (r.id == "Arena") mapa = r;
//         //else if (r.id == "PostoAbastecimento") postoAbastecimento = r;
//     }

//     // pega os 'circle'
//     vector<Circle> circles = this->getCircles();
//     for (Circle c : circles) {
//         arena.mapaCorID[c.id] = c.cor;
//         if (c.id == "Jogador") areaJogador = c;
//         else if (c.id == "Inimigo") areaOponente = c;
//         //else if (c.id == "ObjetoResgate") objetosResgate.push_back(c);
//     }

//     // monta a arena
//     arena.mapa = mapa;
//     //arena.postoAbastecimento = postoAbastecimento;
//     //arena.objetosResgate = objetosResgate;

//     areaJogador.posicao.z = TAMANHO_LUTADORES / 2.0;
//     arena.jogador.area = areaJogador;
//     arena.jogador.id = areaJogador.id;
//     arena.jogador.velocidadeHelicoptero = velocidadeLutador;
//     // printf("%f\n",arena.jogador.area.raio/2.0);
//     // printf("%f\n", TAMANHO_LUTADORES / 2.0);
//     // printf("%f\n",areaJogador.posicao.z);
//     // areaJogador.posicao.z = arena.jogador.area.raio/2.0;
    
//     //arena.jogador.velocidadeTiro = _velTiro;
//     //arena.jogador.tempoMaximoDeVoo = _tempoDeVoo;
//     arena.jogador.corCorpo = Cor("lightgreen");


//     areaOponente.posicao.z = TAMANHO_LUTADORES / 2.0;
//     arena.oponente.area = areaOponente;
//     arena.oponente.id = areaOponente.id;
//     arena.oponente.velocidadeHelicoptero = velocidadeOponente;
//     // areaOponente.posicao.z = arena.oponente.area.raio/2.0;

//     // //arena.jogador.velocidadeTiro = _velTiro;
//     // //arena.jogador.tempoMaximoDeVoo = _tempoDeVoo;
//     arena.oponente.corCorpo = Cor("darkgreen");

//     srand(time(NULL));

//     // for (Circle areaInimigo : areaInimigos) {
//     //     Helicoptero inimigo;
//     //     areaInimigo.posicao.z = TAMANHO_LUTADORES + (rand() % ((areaJogador.raio * 5) - TAMANHO_LUTADORES * 2));
//     //     inimigo.area = areaInimigo;
//     //     inimigo.id = areaInimigo.id;
//     //     inimigo.velocidadeHelicoptero = _velInimigo;
//     //     inimigo.velocidadeTiro = _velTiro;
//     //     //inimigo.decolar(); // inimigos começam voando
//     //     //arena.inimigos.push_back(inimigo);
//     // }

//     //arena.nObjetos = arena.objetosResgate.size();
//     //arena.nInimigos = arena.inimigos.size();
//     //arena.frequenciaTiro = _freqTiro;

//     return arena;

// }


// vector<Rect> INPUT::getRects()
// {
//     vector<Rect> rects;
//     XMLElement* arenaSVG = this->input.FirstChildElement();

//     // pega os 'rect'
//     for (XMLElement* rect = arenaSVG->FirstChildElement("rect"); rect != NULL; rect = rect->NextSiblingElement("rect"))
//     {
//         Rect r;
//         int _x, _y;
//         rect->QueryIntAttribute("x", &_x);
//         rect->QueryIntAttribute("y", &_y);
//         rect->QueryIntAttribute("width", &r.largura);
//         rect->QueryIntAttribute("height", &r.altura);
//         r.cor = Cor(rect->Attribute("fill"));
//         // if (rect->Attribute("stroke-width")) rect->QueryIntAttribute("stroke-width", &r.strokeLargura);
//         // if (rect->Attribute("stroke")) r.strokeCor = Cor(rect->Attribute("stroke"));
//         r.id = rect->Attribute("id");
//         r.posicao.x = _x;
//         r.posicao.y = _y;
//         rects.push_back(r);
//     }

//     return rects;
// }


// vector<Circle> INPUT::getCircles()
// {
//     vector<Circle> circles;
//     XMLElement* arenaSVG = this->input.FirstChildElement();

//     // pega os 'rect'
//     for (XMLElement* circle = arenaSVG->FirstChildElement("circle"); circle != NULL; circle = circle->NextSiblingElement("circle"))
//     {
//         Circle c;
//         int _x, _y;
//         circle->QueryIntAttribute("cx", &_x);
//         circle->QueryIntAttribute("cy", &_y);
//         circle->QueryIntAttribute("r", &c.raio);
//         c.cor = Cor(circle->Attribute("fill"));
//         c.id = circle->Attribute("id");
//         c.posicao.x = _x;
//         c.posicao.y = _y;
//         circles.push_back(c);
//     }

//     return circles;
// }
