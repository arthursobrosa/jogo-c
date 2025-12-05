#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "coordenada.h"

#define NUM_LINHAS 20
#define NUM_COLUNAS 80
#define ESCALA 16

void lerMapa(char *caminhoArquivo, char mapa[NUM_LINHAS][NUM_COLUNAS], Coordenada *coordenadaJogador, Coordenada *coordenadaInimigo);
void desenharMapa(char mapa[NUM_LINHAS][NUM_COLUNAS]);
void desenharRodape();
void desenharJogador(Coordenada *coordenada, float *angulo);
void desenharInimigo(Coordenada *coordenada, float *angulo);
void _desenharCarro(Coordenada *coordenada, float angulo, Color cor);
void _desenharCelulaMapa(Coordenada *origemMapa, char *c);
void _desenharRetangulo(Rectangle *celula, float angulo, Color cor);