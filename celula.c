#include <raylib.h>
#include "celula.h"

void desenharCelula(Celula celula)
{
    float x = celula.retangulo.x * ESCALA;
    float y = celula.retangulo.y * ESCALA;
    float largura = celula.retangulo.width * ESCALA;
    float altura = celula.retangulo.height * ESCALA;
    Rectangle retangulo = {x, y, largura, altura};

    DrawRectanglePro(
        retangulo,
        (Vector2){0, 0},
        celula.angulo,
        celula.cor
    );
}