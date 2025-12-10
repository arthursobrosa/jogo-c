#include <string.h>
#include "janela.h"

int main(/*int argc, char *argv[]*/)
{
    /*if (argc != 2)
    {
        printf("Uso: %s <arquivo_mapa>\n", argv[0]);
        return 1;
    }*/

    char caminhoArquivo[20]="mapa.txt";
    //strcpy(caminhoArquivo, argv[1]);
    char mapaChar[NUM_LINHAS][NUM_COLUNAS];
    Celula mapaCel[NUM_LINHAS][NUM_COLUNAS];
    EstadoJogo estado;
    Jogador voce = {0};
    Jogador inimigo = {0};
    estado.menuAtivo = true;
    voce.vida=100;
    inimigo.vida=100;

    lerMapa(caminhoArquivo,mapaChar,&voce,&inimigo);

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

        if(estado.menuAtivo){
            exibirMenu(&estado,caminhoArquivo, mapaChar, &voce, &inimigo);
        } else{

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

        DrawText(TextFormat("Vida: %i", &voce.vida), 10, 10, 20, BLACK);

        EndDrawing();
        }
    }
     /*BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(TextFormat("SCORE: %i", score), 280, 130, 40, MAROON);
            DrawText(TextFormat("HI-SCORE: %i", hiscore), 210, 200, 50, BLACK);

            DrawText(TextFormat("frames: %i", framesCounter), 10, 10, 20, LIME);

            DrawText("Press R to generate random numbers", 220, 40, 20, LIGHTGRAY);
            DrawText("Press ENTER to SAVE values", 250, 310, 20, LIGHTGRAY);
            DrawText("Press SPACE to LOAD values", 252, 350, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }*/


    CloseWindow();

    return 0;
}
