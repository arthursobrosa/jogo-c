typedef struct 
{
    float largura;
    float altura;
} Tamanho;

#define ESCALA 16

void definirTamanhos(Tamanho *tamMapa, Tamanho *tamRodape, Tamanho *tamJanela, int numLinhas, int numColunas, int escala);