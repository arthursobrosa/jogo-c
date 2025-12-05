#include "movimento.h"

void mover(bool isPositive, float *velocidade, float *angulo, double *x, double *y)
{
    float anguloRad = *angulo * (M_PI / 180);
    float deslocamentoX = *velocidade * cos(anguloRad);
    float deslocamentoY = *velocidade * sin(anguloRad);

    if (isPositive)
    {
        *x += deslocamentoX;
        *y += deslocamentoY;
    }
    else
    {
        *x -= deslocamentoX;
        *y -= deslocamentoY;
    }
}