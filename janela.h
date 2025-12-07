#include <stdlib.h>
#include "jogador.h"

#define NUM_LINHAS 20
#define NUM_COLUNAS 80

void lerMapa
(
    char *caminhoArquivo,
    char mapaChar[NUM_LINHAS][NUM_COLUNAS],
    Jogador *voce,
    Jogador *inimigo
);

void desenharMapa
(
    char mapaChar[NUM_LINHAS][NUM_COLUNAS], 
    Celula mapaCel[NUM_LINHAS][NUM_COLUNAS]
);

void _desenharCelulaMapa
(
    int linha, 
    int coluna, 
    char c,
    Celula mapaCel[NUM_LINHAS][NUM_COLUNAS]
);

void desenharRodape(float largura, float altura);

float _produtoEscalar(const Vector2 a, const Vector2 b);

void _obterCantosRetanguloRotacionado
(
    Rectangle retangulo,
    float rotacao,
    Vector2 anchor,
    Vector2 saida[4]
);

void _obterAABBdosCantos
(
    const Vector2 cantos[4], 
    Rectangle *aabb
);

void _projetarPoligono
(
    const Vector2 cantos[4],
    const Vector2 eixo,
    float *limiteMinimo,
    float *limiteMaximo
);

bool _intervalosSeSobrepoem
(
    float minA,
    float maxA,
    float minB,
    float maxB
);

bool _satRetRet(const Vector2 a[4], const Vector2 b[4]);
bool _ehParede(Celula celula);

bool temParede(
    Celula mapaCel[NUM_LINHAS][NUM_COLUNAS],
    Jogador *jogador
);