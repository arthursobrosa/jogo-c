#include <stdio.h>
#include <stdlib.h>
#include "desenho.h"

void lerMapa(char *caminhoArquivo, char mapa[NUM_LINHAS][NUM_COLUNAS], Coordenada *origemJogador, Coordenada *origemInimigo)
{
    FILE *arquivo = fopen(caminhoArquivo, "r");

    if (!arquivo) 
    {
        printf("Erro ao abrir arquivo do mapa!\n");
        return;
    }

    char linha[100];

    for (int i = 0; i < NUM_LINHAS; i++) 
    {
        fgets(linha, sizeof(linha), arquivo);

        for (int j = 0; j < NUM_COLUNAS; j++) 
        {
            char c = linha[j];

            if (c == 'i')
            {
                origemJogador->x = j * ESCALA;
                origemJogador->y = i * ESCALA;
            }

            if (c == 'j')
            {
                origemInimigo->x = j * ESCALA;
                origemInimigo->y = i * ESCALA;
            }

            mapa[i][j] = c;
        }
    }

    fclose(arquivo);
}

void desenharMapa(char mapa[NUM_LINHAS][NUM_COLUNAS])
{
    for (int i = 0; i < NUM_LINHAS; i++)
    {
        for (int j = 0; j < NUM_COLUNAS; j++)
        {
            Coordenada origemMapa = {i, j};
            char c = mapa[i][j];

            _desenharCelulaMapa(&origemMapa, &c);
        }
    }
}

void desenharRodape()
{
    Rectangle *celula = malloc(sizeof(Rectangle));

    celula->x = 0;
    celula->y = NUM_LINHAS * ESCALA;
    celula->width = NUM_COLUNAS * ESCALA;
    celula->height = NUM_LINHAS * ESCALA * 0.15;

    _desenharRetangulo(celula, BLUE);

    free(celula);
}

void desenharJogador(Coordenada *origem)
{
    _desenharCarro(origem, YELLOW);
}

void desenharInimigo(Coordenada *origem)
{
    _desenharCarro(origem, RED);
}

void _desenharCarro(Coordenada *origem, Color cor)
{
    Rectangle *celula = malloc(sizeof(Rectangle));

    float largura = 48;
    float altura = 16;

    celula->x = origem->x;
    celula->y = origem->y;
    celula->width = largura;
    celula->height = altura;

    _desenharRetangulo(celula, cor);

    free(celula);
}

void _desenharCelulaMapa(Coordenada *origemMapa, char *c)
{
    Rectangle *celula = malloc(sizeof(Rectangle));

    celula->x = origemMapa->y * ESCALA;
    celula->y = origemMapa->x * ESCALA;
    celula->width = ESCALA;
    celula->height = ESCALA;

    Color cor;

    switch (*c)
    {
        case 'p':
            cor = BROWN;
            break;
        case 'L':
            cor = PINK;
            break;
        default:
            cor = WHITE;
    }

    _desenharRetangulo(celula, cor);

    free(celula);
}

void _desenharRetangulo(Rectangle *celula, Color cor)
{
    // DrawRectangleRec(*celula, cor);
    // DrawRectangleLinesEx(*celula, 0.5, BLACK);

    DrawRectangle
    (
        celula->x,
        celula->y,
        celula->width,
        celula->height,
        cor
    );
}