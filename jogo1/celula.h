#include <stdio.h>
#include <raylib.h>

#define ESCALA 16

typedef struct
{
    Rectangle retangulo;
    Vector2 ancoraRotacao;
    float angulo;
    float anguloFuturo;
    Color cor;
    Vector2 posicaoFutura;

} Celula;

void desenharCelula(Celula celula);
