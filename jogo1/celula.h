#include <stdio.h>
#include <raylib.h>
#include <math.h>
#define ESCALA 16
#define TILE_UNIT 1.0f

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
