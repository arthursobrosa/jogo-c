#include <stdio.h>
#include <stdlib.h>
#include "jogador.h"

#define NUM_LINHAS 20
#define NUM_COLUNAS 80
#define ESCALA 16

void lerMapa(char *caminhoArquivo, char mapa[NUM_LINHAS][NUM_COLUNAS], Coordenada *coordenadaVoce, Coordenada *coordenadaInimigo);
void desenharMapa(char mapa[NUM_LINHAS][NUM_COLUNAS]);
void desenharRodape(Tamanho tamanho);
void desenharJogador(Jogador *jogador);
void _desenharCelulaMapa(Coordenada *origemMapa, char *c);
void _desenharRetangulo(Rectangle *celula, float angulo, Color cor);