#include <stdlib.h>
#include "jogador.h"

#define NUM_LINHAS 20
#define NUM_COLUNAS 80

void lerMapa(
    char *caminhoArquivo,
    char mapa[NUM_LINHAS][NUM_COLUNAS],
    Jogador *voce,
    Jogador *inimigo
);

void desenharMapa(char mapa[NUM_LINHAS][NUM_COLUNAS]);
void _desenharCelulaMapa(int linha, int coluna, char c);
void desenharRodape(float largura, float altura);
bool temParede(char mapa[NUM_LINHAS][NUM_COLUNAS], Jogador *jogador);