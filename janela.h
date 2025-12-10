#include <stdlib.h>

#include "jogador.h"
#include "caixa.h"

#define NUM_LINHAS 20
#define NUM_COLUNAS 80

typedef struct {
    bool menuAtivo;
    Jogador voce;
    Jogador inimigo;
    bool venceu;
    bool perdeu;
    //posicao inimigo
    //posicao jogador
    // posicao caixas
}EstadoJogo; //salvar as info importantes

void exibirMenu( EstadoJogo *estado, char *caminhoArquivo, char mapaChar[NUM_LINHAS][NUM_COLUNAS], Jogador *voce, Jogador *inimigo);
void salvarJogo(EstadoJogo *estado);
void carregarJogo(EstadoJogo *estado);

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
void desenharInformacoes(Jogador *voce, Jogador *inimigo, EstadoJogo *estado);

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
void exibirVitoria(EstadoJogo *estado);
void exibirGameOver(EstadoJogo *estado);

//0=void desenharCaixa()
