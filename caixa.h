//nao funciona ainda
/*
#include <stdlib.h> 
#include <time.h>  
#include <math.h> 
#include <stdlib.h>

#define ITEM_NULO               0
#define ITEM_ARMA               1  
#define ITEM_ESCUDO             2  
#define ITEM_BOMBA              3  
#define ITEM_BONUS_VELOCIDADE   4

typedef struct {
    Vector2 posicao;        
    int itemContido;       
    bool ativa;             
} Caixa;
typedef struct {
    Vector2 posicao;
    Vector2 velocidade;
    float angulo;      
    bool ativo;        
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
}*/
