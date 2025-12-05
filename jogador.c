#include "jogador.h"

void mover(bool ehPositivo, Jogador *jogador)
{
    float anguloRad = jogador->angulo * (M_PI / 180);
    float deslocamentoX = jogador->velocidade * cos(anguloRad);
    float deslocamentoY = jogador->velocidade * sin(anguloRad);

    if (ehPositivo)
    {
        jogador->posicao.x += deslocamentoX;
        jogador->posicao.y += deslocamentoY;
    }
    else
    {
        jogador->posicao.x -= deslocamentoX;
        jogador->posicao.y -= deslocamentoY;
    }
}

void configurarJogador(bool ehInimigo, Jogador *jogador, float velocidade)
{
    float largura = 48;
    float altura = 16;
    jogador->tamanho.largura = largura;
    jogador->tamanho.altura = altura;

    jogador->velocidade = velocidade;

    Color cor;

    if (ehInimigo)
    {
        cor = RED;
    }
    else
    {
        cor = YELLOW;
    }

    jogador->cor = cor;
}