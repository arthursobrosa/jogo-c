#include <stdio.h>
#include <raylib.h>
#include <string.h>
#include "desenho.h"
#include "tamanho.h"
#include "movimento.h"

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

    char mapa[NUM_LINHAS][NUM_COLUNAS];
    Coordenada coordenadaJogador;
    Coordenada coordenadaInimigo;

    float anguloJogador = 0;
    float anguloInimigo = 0;

    lerMapa(caminhoArquivo, mapa, &coordenadaJogador, &coordenadaInimigo);

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
        desenharJogador(&coordenadaJogador, &anguloJogador);
        desenharInimigo(&coordenadaInimigo, &anguloInimigo);

        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) 
        {
            mover(false, &velocidade, &anguloJogador, &(coordenadaJogador.x), &(coordenadaJogador.y));
        }

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) 
        {
            anguloJogador--;
        }

        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) 
        {
            anguloJogador++;
        }

        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) 
        {
            mover(true, &velocidade, &anguloJogador, &(coordenadaJogador.x), &(coordenadaJogador.y));
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}