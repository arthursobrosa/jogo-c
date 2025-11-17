#include "raylib.h"
#include <stdio.h>

#define NUM_LINHAS 20
#define NUM_COLUNAS 80
#define CELULA_LARGURA 12
#define CELULA_ALTURA 20
#define MARGEM 40

void parseMap(char mapa[NUM_LINHAS][NUM_COLUNAS], int *linhaInicial, int *colunaInicial);

int main(void) {
    char mapa[NUM_LINHAS][NUM_COLUNAS];
    int linha;
    int coluna;

    parseMap(mapa, &linha, &coluna);

    int frame_largura = (CELULA_LARGURA * NUM_COLUNAS) + (MARGEM * 2);
    int frame_altura = (CELULA_ALTURA * NUM_LINHAS) + (MARGEM * 2);

    InitWindow(frame_largura, frame_altura, "Movimento");
    SetTargetFPS(60);

    Image paredeImage = LoadImage("resources/parede.jpg");
    Texture2D paredeTexture = LoadTextureFromImage(paredeImage);
    UnloadImage(paredeImage);

    Image pistaImage = LoadImage("resources/pista.jpg");
    Texture2D pistaTexture = LoadTextureFromImage(pistaImage);
    UnloadImage(pistaImage);

    int novaLinha = linha;
    int novaColuna = coluna;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        Rectangle pistaDest = {
            MARGEM,
            MARGEM,
            CELULA_LARGURA * NUM_COLUNAS,
            CELULA_ALTURA * NUM_LINHAS
        };

        Rectangle pistaSrc = { 0, 0, pistaTexture.width, pistaTexture.height };

        DrawTexturePro(
            pistaTexture,
            pistaSrc,
            pistaDest,
            (Vector2){0,0},
            0.0f,
            WHITE
        );

        int posX, posY;

        for (int i = 0; i < NUM_LINHAS; i++) {
            posY = i * CELULA_ALTURA + MARGEM;

            for (int j = 0; j < NUM_COLUNAS; j++) {
                posX = j * CELULA_LARGURA + MARGEM;

                Rectangle src;

                Rectangle dest = { 
                    posX, 
                    posY,
                    CELULA_LARGURA,
                    CELULA_ALTURA  
                };

                Vector2 origin = { 0, 0 };

                switch (mapa[i][j]) {
                    case 'p':
                        src = (Rectangle){ 0, 0, paredeTexture.width, paredeTexture.height };

                        DrawTexturePro(
                            paredeTexture,
                            src,
                            dest,
                            origin,
                            0.0f,
                            WHITE
                        );

                        continue;
                    case 'i':
                        DrawRectangle(
                            posX,
                            posY,
                            CELULA_LARGURA,
                            CELULA_ALTURA,
                            GREEN
                        );
                        continue;
                    case 'L':
                        DrawRectangle(
                            posX,
                            posY,
                            CELULA_LARGURA,
                            CELULA_ALTURA,
                            PINK
                        );
                        continue;
                    default:
                        continue;
                }
            }
        }

        if (IsKeyDown(KEY_UP)) novaLinha--;
        if (IsKeyDown(KEY_DOWN)) novaLinha++;
        if (IsKeyDown(KEY_RIGHT)) novaColuna++;
        if (IsKeyDown(KEY_LEFT)) novaColuna--;

        if (novaLinha >= 0 && novaLinha < NUM_LINHAS &&
            novaColuna >= 0 && novaColuna < NUM_COLUNAS &&
            mapa[novaLinha][novaColuna] != 'p'
        ) {
            linha = novaLinha;
            coluna = novaColuna;
        } else {
            novaLinha = linha;
            novaColuna = coluna;
        } 

        if (mapa[novaLinha][novaColuna] == 'L') {
            break;
        }

        DrawRectangle(
            coluna * CELULA_LARGURA + MARGEM,
            linha * CELULA_ALTURA + MARGEM,
            CELULA_LARGURA,
            CELULA_ALTURA,
            RED
        );

        EndDrawing();
    }

    UnloadTexture(paredeTexture);
    UnloadTexture(pistaTexture);
    CloseWindow();

    return 0;
}

void parseMap(char mapa[NUM_LINHAS][NUM_COLUNAS], int *linhaInicial, int *colunaInicial) {
    FILE *file = fopen("mapa.txt", "r");

    if (!file) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    char linha[100];

    for (int i = 0; i < NUM_LINHAS; i++) {
        fgets(linha, sizeof(linha), file);

        for (int j = 0; j < NUM_COLUNAS; j++) {
            char c = linha[j];

            if (c == 'i') {
                *linhaInicial = i;
                *colunaInicial = j;
            }

            mapa[i][j] = c;
        }
    }

    fclose(file);
}