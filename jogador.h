#include <raylib.h>
#include <stdbool.h>
#include <math.h>
#include "helper.h"

typedef struct 
{
    Coordenada posicao;
    Tamanho tamanho;
    float velocidade;
    float angulo;
    Color cor;
} Jogador;

void configurarJogador(bool ehInimigo, Jogador *jogador, float velocidade);
void mover(bool ehPositivo, Jogador *jogador);