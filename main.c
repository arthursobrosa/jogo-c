#include <string.h>
#include "janela.h"

int main(int argc, char *argv[]) 
{
    if (argc != 2)
    {
        printf("Uso: %s <arquivo_mapa>\n", argv[0]);
        return 1;
    }

    char caminhoArquivo[20];
    strcpy(caminhoArquivo, argv[1]);
    char mapaChar[NUM_LINHAS][NUM_COLUNAS];
    Celula mapaCel[NUM_LINHAS][NUM_COLUNAS];

    Jogador voce = {0};
    Jogador inimigo = {0};

    lerMapa(
        caminhoArquivo,
        mapaChar,
        &voce,
        &inimigo
    );

    configurarJogadores(&voce, &inimigo);

    float larguraMapa = NUM_COLUNAS;
    float alturaMapa = NUM_LINHAS;

    float larguraRodape = larguraMapa;
    float alturaRodape = alturaMapa * 0.15;

    float larguraJanela = larguraMapa;
    float alturaJanela = alturaMapa + alturaRodape;

    InitWindow(
        larguraJanela * ESCALA, 
        alturaJanela * ESCALA, 
        "Janela do Jogo"
    );

    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        lidarComTecla(&voce);

        if (!temParede(mapaCel, &voce))
        {
            atualizarJogador(&voce);
        }
        else
        {
            resetarJogador(&voce);
        }

        BeginDrawing();
        ClearBackground(WHITE);

        desenharMapa(mapaChar, mapaCel);
        desenharRodape(larguraRodape, alturaRodape);
        desenharJogador(&voce);
        desenharJogador(&inimigo);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}