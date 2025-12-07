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
        jogador->celula.anguloFuturo -= 120.0 * GetFrameTime();
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        jogador->celula.anguloFuturo += 120.0 * GetFrameTime();
    }
}

void _acelerar(Jogador *jogador, bool praFrente)
{
    float deltaTempo = GetFrameTime();
    float aceleracaoReal = ACELERACAO * deltaTempo;
    float moduloVelocidade = fabsf(jogador->velocidade);

    if (moduloVelocidade < VELOCIDADE_MAXIMA && (moduloVelocidade + aceleracaoReal) <= VELOCIDADE_MAXIMA)
    {
        if (praFrente)
        {
            jogador->velocidadeFutura += aceleracaoReal;
        }
        else {
            jogador->velocidadeFutura -= aceleracaoReal;
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
    float deltaTempo = GetFrameTime();
    float frenagem = ACELERACAO * deltaTempo;

    if (jogador->velocidade > 0)
    {
        jogador->velocidadeFutura -= frenagem;
        if (jogador->velocidadeFutura < 0)
            jogador->velocidadeFutura = 0;
    }
    else if (jogador->velocidade < 0)
    {
        jogador->velocidadeFutura += frenagem;
        if (jogador->velocidadeFutura > 0)
            jogador->velocidadeFutura = 0;
    }

    _mover(jogador);
}

void _mover(Jogador *jogador)
{
    float anguloRad = jogador->celula.anguloFuturo * (M_PI / 180);
    float deltaTempo = GetFrameTime();
    float deslocamento = jogador->velocidadeFutura * deltaTempo;
    float deslocamentoX = deslocamento * cos(anguloRad);
    float deslocamentoY = deslocamento * sin(anguloRad);

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

void resetarJogador(Jogador *jogador)
{
    jogador->celula.posicaoFutura.x = jogador->celula.retangulo.x;
    jogador->celula.posicaoFutura.y = jogador->celula.retangulo.y;
    jogador->celula.anguloFuturo = jogador->celula.angulo;
    jogador->velocidade *= 0.5;
    jogador->velocidadeFutura = jogador->velocidade;
}