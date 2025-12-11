
#include "janela.h"
#include <raylib.h>
#define PROBABILIDADE_ROTACAO_POR_FRAME 0.015f
#define TEMPO_MIN_ROTACAO 0.3f
#define TEMPO_MAX_ROTACAO 1.5f
#define DISTANCIA_VERIFICACAO 2.0f
#define TEMPO_REVERSO 0.7f
#define TILE_UNIT 1.0f

// --- PROTÓTIPOS DAS FUNÇÕES DA IA ---

// 1. Função principal de controle da IA
void lidarComIA(Jogador *inimigo, Jogador *jogador, char mapaChar[NUM_LINHAS][NUM_COLUNAS]);

// 2. Lógica de uso de itens
//void GerenciarUsoItemIA(Jogador *inimigo, Jogador *alvo);

// 3. Função de verificação de obstáculos
bool VerificarParedeProxima(char mapaChar[NUM_LINHAS][NUM_COLUNAS], float angulo, int linhaAtual, int colunaAtual);

