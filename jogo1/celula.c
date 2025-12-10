
#include "celula.h"

void desenharCelula(Celula celula)
{
    float largura = celula.retangulo.width * ESCALA;
    float altura = celula.retangulo.height * ESCALA;

    Vector2 ancoraRotacaoReal = celula.ancoraRotacao;
    if (celula.ancoraRotacao.x < 0) ancoraRotacaoReal.x = 0;
    if (celula.ancoraRotacao.x > 1) ancoraRotacaoReal.x = 1;
    if (celula.ancoraRotacao.y < 0) ancoraRotacaoReal.y = 0;
    if (celula.ancoraRotacao.y > 1) ancoraRotacaoReal.y = 1;

    Vector2 eixoRotacao =
    {
        largura * ancoraRotacaoReal.x,
        altura * ancoraRotacaoReal.y
    };

    float x = (celula.retangulo.x * ESCALA) + eixoRotacao.x;
    float y = (celula.retangulo.y * ESCALA) + eixoRotacao.y;
    Rectangle retangulo = {x, y, largura, altura};

    DrawRectanglePro(
        retangulo,
        eixoRotacao,
        celula.angulo,
        celula.cor
    );
}
