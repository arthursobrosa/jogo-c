#include <stdio.h>
#include <raylib.h>

#define ESCALA 16

typedef struct
{
    Rectangle retangulo;
    float angulo;
    Color cor;
} Celula;

void desenharCelula(Celula celula);