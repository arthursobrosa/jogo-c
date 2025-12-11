#include <string.h>
#include "inimigo.h"



int main(/*int argc, char *argv[]*/)
{
    /*if (argc != 2)
    {
        printf("Uso: %s <arquivo_mapa>\n", argv[0]);
        return 1;
    }*/

    char caminhoArq[20]="mapa.txt";
    //strcpy(caminhoArquivo, argv[1]);
    char mapaChar[NUM_LINHAS][NUM_COLUNAS];
    Celula mapaCel[NUM_LINHAS][NUM_COLUNAS];
    EstadoJogo estado;

    Jogador voce = {0};
    Jogador inimigo = {0};
    Jogador jogador;
    estado.menuAtivo=true;
    estado.venceu=false;
    estado.perdeu=false;
    voce.voltas=0;
    inimigo.voltas=0;
    voce.vida=100;
    inimigo.vida=100;

     InitAudioDevice();

    Music music = LoadMusicStream("rock.m4a");

    lerMapa(caminhoArq,mapaChar,&voce,&inimigo);

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
        lidarComIA(&inimigo, &voce, mapaChar);
        if (!temParede(mapaCel, &inimigo))
        {
            // Se não houver colisão na posição FUTURA, atualiza a posição ATUAL
            atualizarJogador(&inimigo);
        }
        else
        {
            // HOUVE COLISÃO!

            // Se a IA está no meio de uma manobra de Ré/Desprendimento,
            // não precisamos de um reset completo que anule a velocidade de ré.
            if (inimigo.estaVirando)
            {
                // Apenas para garantir que o carro pare na parede e não passe,
                // mas não zera a velocidade futura, permitindo que o _acelerar(false) da IA funcione no próximo frame.
                _frear(&inimigo); // Freia para anular a velocidade de avanço
            }
            else
            {
                // Se a IA não estava em manobra ativa, a colisão foi inesperada (bug ou ângulo ruim).
                // Reseta o jogador.
                resetarJogador(&inimigo);
            }
        }

        // 3. Atualização do Jogador (Voce) - Garanta que está separado do inimigo
        if (!temParede(mapaCel, &voce))
        {
            atualizarJogador(&voce);
        } else {
            resetarJogador(&voce);
        }

        if(estado.menuAtivo){
            exibirMenu(&estado,caminhoArq, mapaChar, &voce, &inimigo);
        } else{

        if (IsKeyPressed(KEY_TAB)) {
            estado.menuAtivo = true;
        }
        VerificarLinhaChegada(&voce, mapaCel, &estado);
        VerificarLinhaChegada(&inimigo, mapaCel, &estado);
         if(inimigo.vida==0 || voce.voltas==3){
            exibirVitoria(&estado);
            continue;
        }
        if(voce.vida==0 || inimigo.voltas==3){
            exibirGameOver(&estado);
            continue;
        }

        BeginDrawing();
        ClearBackground(WHITE);

        desenharMapa(mapaChar, mapaCel);
        desenharRodape(larguraRodape, alturaRodape);
        desenharJogador(&voce);
        desenharJogador(&inimigo);
        desenharInformacoes(&voce, &inimigo);

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

