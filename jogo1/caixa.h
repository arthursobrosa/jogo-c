//nao funciona ainda
/*
#include <stdlib.h> // Para a função rand()
#include <time.h>   // Para a função time()
#include <math.h> // Necessário para sinf e cosf
#include <stdlib.h>

#define ITEM_NULO               0
#define ITEM_ARMA               1  // Permite disparar um tiro [cite: 128]
#define ITEM_ESCUDO             2  // Ativa proteção, aguentando um tiro ou bomba [cite: 131]
#define ITEM_BOMBA              3  // Colisão diminui a vida em 50 pontos [cite: 135]
#define ITEM_BONUS_VELOCIDADE   4

typedef struct {
    Vector2 posicao;        // Posição (x, y) na tela, do tipo Vector2 da raylib
    int itemContido;        // Usa as constantes (ITEM_ARMA, ITEM_ESCUDO, etc.)
    bool ativa;             // Indica se a caixa está visível na pista
} Caixa;
typedef struct {
    Vector2 posicao;
    Vector2 velocidade; // Vetor de velocidade (direção e magnitude)
    float angulo;       // Ângulo de disparo
    bool ativo;         // Se o projétil está sendo renderizado e movido
} Projetil;
typedef struct {
    Vector2 posicao;
    bool ativa; // Indica se a bomba está no chão
} Bomba;
void VerificarColisaoBomba(Carro *carro, Bomba *bombas, int numBombas) {
    for (int i = 0; i < numBombas; i++) {
        if (bombas[i].ativa) {
            // Verifica a colisão entre o carro e a bomba
            if (CheckCollisionCircles(carro->posicao, 15.0f, bombas[i].posicao, 10.0f)) {

                // Se um carro colidir com uma bomba, sua vida diminui em 50 pontos [cite: 135]
                ReceberDano(carro, 50);

                // A bomba explode e desaparece
                bombas[i].ativa = false;

                // O escudo pode aguentar esta explosão [cite: 131, 132]
            }
        }
    }
}
*/
