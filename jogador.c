#include "jogador.h"

void configurarJogadores(Jogador *voce, Jogador *inimigo)
{
    float largura = 3;
    float altura = 1;

    voce->celula.retangulo.width = largura;
    voce->celula.retangulo.height = altura;
    voce->celula.ancoraRotacao = (Vector2){0.5, 0.5};
    voce->celula.cor = BLUE;
    voce->velocidade = 0;

    inimigo->celula.retangulo.width = largura;
    inimigo->celula.retangulo.height = altura;
    inimigo->celula.ancoraRotacao = (Vector2){0.5, 0.5};
    inimigo->celula.cor = RED;
    inimigo->velocidade = 0;
}

void desenharJogador(Jogador *jogador)
{
    desenharCelula(jogador->celula);
}

void lidarComTecla(Jogador *jogador)
{
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        _avancar(jogador);
    }
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        _voltar(jogador);
    }
    else 
    {
        _frear(jogador);
    }

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        jogador->celula.anguloFuturo -= 3;
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        jogador->celula.anguloFuturo += 3;
    }
}

void _acelerar(Jogador *jogador, bool praFrente)
{
    if (fabsf(jogador->velocidade) <= VELOCIDADE_MAXIMA)
    {
        if (praFrente)
        {
            jogador->velocidadeFutura += ACELERACAO;
        }
        else {
            jogador->velocidadeFutura -= ACELERACAO;
        }
    }
}

void _avancar(Jogador *jogador)
{
    _acelerar(jogador, true);
    _mover(jogador);
}

void _voltar(Jogador *jogador)
{
    _acelerar(jogador, false);
    _mover(jogador);
}

void _frear(Jogador *jogador)
{
    if (fabsf(jogador->velocidade) < 0.0001f) return;

    bool aceleracaoEhPositiva = jogador->velocidade > 0;

    if (aceleracaoEhPositiva)
    {
        _voltar(jogador);
    }
    else 
    {
        _avancar(jogador);
    }
}

void _mover(Jogador *jogador)
{
    float anguloRad = jogador->celula.anguloFuturo * (M_PI / 180);
    float deslocamentoX = jogador->velocidadeFutura * cos(anguloRad);
    float deslocamentoY = jogador->velocidadeFutura * sin(anguloRad);

    float novoX = (jogador->celula.retangulo.x) + deslocamentoX;
    float novoY = (jogador->celula.retangulo.y) + deslocamentoY;
    Vector2 coordenada = {novoX, novoY};

    jogador->celula.posicaoFutura = coordenada;
}

void atualizarJogador(Jogador *jogador)
{
    jogador->celula.retangulo.x = jogador->celula.posicaoFutura.x;
    jogador->celula.retangulo.y = jogador->celula.posicaoFutura.y;
    jogador->celula.angulo = jogador->celula.anguloFuturo;
    jogador->velocidade = jogador->velocidadeFutura;
}