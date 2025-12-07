#include <stdbool.h>
#include <math.h>
#include "celula.h"

#define VELOCIDADE_MAXIMA 50.0
#define ACELERACAO 20.0

typedef struct 
{
    Celula celula;
    float velocidade;
    float velocidadeFutura;
} Jogador;

void configurarJogadores(Jogador *voce, Jogador *inimigo);
void desenharJogador(Jogador *jogador);
void lidarComTecla(Jogador *jogador);
void _acelerar(Jogador *jogador, bool praFrente);
void _avancar(Jogador *jogador);
void _voltar(Jogador *jogador);
void _frear(Jogador *jogador);
void _mover(Jogador *jogador);
void atualizarJogador(Jogador *jogador);
void resetarJogador(Jogador *jogador);