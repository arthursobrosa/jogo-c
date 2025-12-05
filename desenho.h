#include <raylib.h>
#include "coordenada.h"

#define NUM_LINHAS 20
#define NUM_COLUNAS 80
#define ESCALA 16

void lerMapa(char *caminhoArquivo, char mapa[NUM_LINHAS][NUM_COLUNAS], Coordenada *origemJogador, Coordenada *origemInimigo);
void desenharMapa(char mapa[NUM_LINHAS][NUM_COLUNAS]);
void desenharRodape();
void desenharJogador(Coordenada *origem);
void desenharInimigo(Coordenada *origem);
void _desenharCarro(Coordenada *origem, Color cor);
void _desenharCelulaMapa(Coordenada *origemMapa, char *c);
void _desenharRetangulo(Rectangle *celula, Color cor);