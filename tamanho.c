#include "tamanho.h"

void definirTamanhos(Tamanho *tamMapa, Tamanho *tamRodape, Tamanho *tamJanela, int numLinhas, int numColunas, int escala) 
{
    tamMapa->largura = numColunas * escala;
    tamMapa->altura = numLinhas * escala;

    tamRodape->largura = tamMapa->largura;
    tamRodape->altura = tamMapa->altura * 0.15;

    tamJanela->largura = tamMapa->largura;
    tamJanela->altura = tamMapa->altura + tamRodape->altura;
}