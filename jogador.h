#include <stdbool.h>
#include <math.h>
#include "celula.h"

#define VELOCIDADE_MAXIMA 1.0
#define ACELERACAO 0.01

typedef struct 
{
    Celula celula;
    float velocidade;
    float velocidadeFutura;
    float aceleracao;
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