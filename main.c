#include <stdio.h>
#include <raylib.h>
#include <string.h>
#include "desenho.h"
#include "tamanho.h"

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
    Coordenada origemJogador;
    Coordenada origemInimigo;

    lerMapa(caminhoArquivo, mapa, &origemJogador, &origemInimigo);

    Tamanho tamanhoMapa;
    Tamanho tamanhoRodape;
    Tamanho tamanhoJanela;

    definirTamanhos(&tamanhoMapa, &tamanhoRodape, &tamanhoJanela, NUM_LINHAS, NUM_COLUNAS, ESCALA);

    InitWindow((int)tamanhoJanela.largura, (int)tamanhoJanela.altura, "Janela do Jogo");
    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(WHITE);

        desenharMapa(mapa);
        desenharRodape();
        desenharJogador(&origemJogador);
        desenharInimigo(&origemInimigo);

        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) 
        {

        }

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) 
        {
            
        }

        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) 
        {
            
        }

        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) 
        {
            
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}