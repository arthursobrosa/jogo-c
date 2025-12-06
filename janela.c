#include "janela.h"

void lerMapa(
    char *caminhoArquivo, 
    char mapa[NUM_LINHAS][NUM_COLUNAS], 
    Jogador *voce, 
    Jogador *inimigo
)
{
    FILE *arquivo = fopen(caminhoArquivo, "r");

    if (!arquivo) 
    {
        printf("Erro ao abrir arquivo do mapa!\n");
        return;
    }

    char linhaDeTexto[100];

    for (int linha = 0; linha < NUM_LINHAS; linha++) 
    {
        fgets(linhaDeTexto, sizeof(linhaDeTexto), arquivo);

        for (int coluna = 0; coluna < NUM_COLUNAS; coluna++) 
        {
            char c = linhaDeTexto[coluna];

            if (c == 'j')
            {
                voce->celula.retangulo.x = coluna;
                voce->celula.retangulo.y = linha;
            }

            if (c == 'i')
            {
                inimigo->celula.retangulo.x = coluna;
                inimigo->celula.retangulo.y = linha;
            }

            mapa[linha][coluna] = c;
        }
    }

    fclose(arquivo);
}

void desenharMapa(char mapa[NUM_LINHAS][NUM_COLUNAS])
{
    for (int linha = 0; linha < NUM_LINHAS; linha++)
    {
        for (int coluna = 0; coluna < NUM_COLUNAS; coluna++)
        {
            _desenharCelulaMapa(linha, coluna, mapa[linha][coluna]);
        }
    }
}

void _desenharCelulaMapa(int linha, int coluna, char c)
{
    Celula celula;
    celula.retangulo.x = coluna;
    celula.retangulo.y = linha;
    celula.retangulo.width = 1;
    celula.retangulo.height = 1;

    Color cor;

    switch (c)
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

    celula.cor = cor;
    celula.angulo = 0;

    desenharCelula(celula);
}

void desenharRodape(float largura, float altura)
{
    Celula celula;
    celula.retangulo.x = 0;
    celula.retangulo.y = (float)NUM_LINHAS;
    celula.retangulo.width = largura;
    celula.retangulo.height = altura;
    celula.angulo = 0;
    celula.cor = YELLOW;

    desenharCelula(celula);
}

bool temParede(char mapa[NUM_LINHAS][NUM_COLUNAS], Jogador *jogador) {
    int linha = (int)(jogador->celula.retangulo.y);
    int coluna = (int)(jogador->celula.retangulo.x);
    return mapa[linha][coluna] == 'p';
}