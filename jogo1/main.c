#include <string.h>

#include "inimigo.h"


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
    Jogador jogador;
    voce.vida=100;
    inimigo.vida=100;
    voce.voltas=0;
    inimigo.voltas=0;
    estado.menuAtivo = true;

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
        lidarComIA(&inimigo);

        if(estado.menuAtivo){
            exibirMenu(&estado,caminhoArquivo, mapaChar, &voce, &inimigo);
        } else{

        if(inimigo.vida==0 || voce.voltas==3){
            estado.venceu=true;
            exibirVitoria(&estado);
            continue;
        }
        if(voce.vida==0 || inimigo.voltas==3){
            estado.perdeu=true;
            exibirGameOver(&estado);
            continue;
        }

        if (IsKeyPressed(KEY_TAB)) {
            estado.menuAtivo = true;
        }

        if (!temObstaculo(mapaCel, &voce, 0))
        {
            atualizarJogador(&voce);
            atualizarJogador(&inimigo);
        }
        if (!temObstaculo(mapaCel, &inimigo, 0))
        {

            atualizarJogador(&inimigo);
        }
        else
        {
            resetarJogador(&voce);
            resetarJogador(&inimigo);
        }
        BeginDrawing();
        ClearBackground(WHITE);

        desenharMapa(mapaChar, mapaCel);
        desenharRodape(larguraRodape, alturaRodape);
        desenharJogador(&voce);
        desenharJogador(&inimigo);
        desenharInformacoes(&voce, &inimigo, &estado);

        EndDrawing();
        }
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

