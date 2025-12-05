#include <stdio.h>
#include <raylib.h>
#include <string.h>
#include "desenho.h"

int main(int argc, char *argv[]) 
{
    if (argc != 2)
    {
        printf("Uso: %s <arquivo_mapa>\n", argv[0]);
        return 1;
    }

    char caminhoArquivo[20];
    strcpy(caminhoArquivo, argv[1]);

    float velocidade = 1;

    Jogador voce;
    Jogador inimigo;
    configurarJogador(false, &voce, velocidade);
    configurarJogador(true, &inimigo, velocidade);

    char mapa[NUM_LINHAS][NUM_COLUNAS];
    lerMapa(caminhoArquivo, mapa, &(voce.posicao), &(inimigo.posicao));

    Tamanho tamanhoMapa = {NUM_COLUNAS * ESCALA, NUM_LINHAS * ESCALA};
    Tamanho tamanhoRodape = {tamanhoMapa.largura, tamanhoMapa.altura * 0.15};
    Tamanho tamanhoJanela = {tamanhoMapa.largura, tamanhoMapa.altura + tamanhoRodape.altura};

    InitWindow((int)tamanhoJanela.largura, (int)tamanhoJanela.altura, "Janela do Jogo");
    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(WHITE);

        desenharMapa(mapa);
        desenharRodape(tamanhoRodape);
        desenharJogador(&voce);
        desenharJogador(&inimigo);

        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) 
        {
            mover(false, &voce);
        }

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) 
        {
            voce.angulo--;
        }

        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) 
        {
            voce.angulo++;
        }

        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) 
        {
            mover(true, &voce);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}