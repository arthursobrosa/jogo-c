#include <stdbool.h>
#include <math.h>
#include "celula.h"

#define VELOCIDADE_MAXIMA 50.0
#define ACELERACAO 20.0

typedef struct
{
    Celula celula;
    Vector2 velocidade;
    Vector2 velocidadeFutura;
    int voltas;
    //caixa
    int vida;
    int inventario;
    bool escudoAtivo;
    float tempoEscudo;
    float tempoVelocidade;
} Jogador;

void configurarJogadores(Jogador *voce, Jogador *inimigo);
void desenharJogador(Jogador *jogador);
void lidarComTecla(Jogador *jogador);
float _modulo(Vector2 vetor);
Vector2 _normalizar(Vector2 vetor);
void _acelerar(Jogador *jogador, bool praFrente);
void _avancar(Jogador *jogador);
void _voltar(Jogador *jogador);
void _frear(Jogador *jogador);
void _girar(Jogador *jogador, bool sentidoHorario);
void _mover(Jogador *jogador);
void atualizarJogador(Jogador *jogador);
void resetarJogador(Jogador *jogador);
void vida(Jogador *voce, Jogador *inimigo);
