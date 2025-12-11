
/*#include <raylib.h>
#include <stdbool.h>
#include "jogador.h"
#define MAX_CAIXAS 10
#define CONST_DURACAO_ESCUDO 5.0f      // Duração do escudo em segundos
#define CONST_DURACAO_BONUS 3.0f

      // Duração do bônus de velocidade em segundos

// --- ENUMERAÇÃO DOS ITENS ---
typedef enum {
    ITEM_NULO = 0,      // Slot vazio
    ITEM_ARMA,          // Disparo frontal
    ITEM_ESCUDO,        // Proteção temporária
    ITEM_BOMBA,         // Mina de retaguarda
    ITEM_BONUS_VELOCIDADE // Aumento de velocidade temporário
} TipoItem;

// --- ESTRUTURA DA CAIXA DE ITEM ---
typedef struct {
    int id;
    Vector2 posicao; // Posição (x, y) no mapa (unidades de célula)
    bool ativo;      // Indica se a caixa está visível e pronta para ser coletada
} Caixa;

// --- PROTÓTIPOS DAS FUNÇÕES DE GERENCIAMENTO ---

// 1. Funções de Item
void UsarItem(Jogador *jogador, EstadoJogo *estado);

// 2. Funções de Caixa/Coleta
void ColetarItem(Jogador *jogador, EstadoJogo *estado);

// 3. Funções de Desenho
void desenharCaixas(EstadoJogo *estado);

// 4. Funções de Efeitos (Chamar no loop principal)
void GerenciarEfeitosTemporarios(Jogador *jogador, float deltaTempo)*/
