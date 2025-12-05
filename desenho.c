#include "desenho.h"

void lerMapa(char *caminhoArquivo, char mapa[NUM_LINHAS][NUM_COLUNAS], Coordenada *coordenadaJogador, Coordenada *coordenadaInimigo)
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

            if (c == 'j')
            {
                coordenadaJogador->x = j * ESCALA;
                coordenadaJogador->y = i * ESCALA;
            }

            if (c == 'i')
            {
                coordenadaInimigo->x = j * ESCALA;
                coordenadaInimigo->y = i * ESCALA;
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

    _desenharRetangulo(celula, 0, BLUE);

    free(celula);
}

void desenharJogador(Coordenada *coordenada, float *angulo)
{
    _desenharCarro(coordenada, *angulo, YELLOW);
}

void desenharInimigo(Coordenada *coordenada, float *angulo)
{
    _desenharCarro(coordenada, *angulo, RED);
}

void _desenharCarro(Coordenada *coordenada, float angulo, Color cor)
{
    Rectangle *celula = malloc(sizeof(Rectangle));

    float largura = 48;
    float altura = 16;

    celula->x = coordenada->x;
    celula->y = coordenada->y;
    celula->width = largura;
    celula->height = altura;

    _desenharRetangulo(celula, angulo, cor);

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

    _desenharRetangulo(celula, 0, cor);

    free(celula);
}

void _desenharRetangulo(Rectangle *celula, float angulo, Color cor)
{
    // DrawRectangleRec(*celula, cor);
    // DrawRectangleLinesEx(*celula, 0.5, BLACK);

    // DrawRectangle
    // (
    //     celula->x,
    //     celula->y,
    //     celula->width,
    //     celula->height,
    //     cor
    // );

    DrawRectanglePro(
        *celula,
        (Vector2){0, 0},
        angulo,
        cor
    );
}