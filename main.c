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
    char mapa[NUM_LINHAS][NUM_COLUNAS];

    Jogador voce = {0};
    Jogador inimigo = {0};

    lerMapa(
        caminhoArquivo,
        mapa,
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
        BeginDrawing();
        ClearBackground(WHITE);

        desenharMapa(mapa);
        desenharRodape(larguraRodape, alturaRodape);
        desenharJogador(&voce);
        desenharJogador(&inimigo);

        lidarComTecla(&voce);
        atualizarJogador(&voce);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}