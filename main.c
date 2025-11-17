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

        for (int i = 0; i < NUM_LINHAS; i++) {
            for (int j = 0; j < NUM_COLUNAS; j++) {
                int posX = j * CELULA_LARGURA + MARGEM;
                int posY = i * CELULA_ALTURA + MARGEM;

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

        if (IsKeyDown(KEY_UP)) linha--;
        if (IsKeyDown(KEY_DOWN)) linha++;
        if (IsKeyDown(KEY_RIGHT)) coluna++;
        if (IsKeyDown(KEY_LEFT)) coluna--;

        if (linha < 0 || linha >= NUM_LINHAS ||
            coluna < 0 || coluna >= NUM_COLUNAS ||
            mapa[linha][coluna] == 'p'
        ) {
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