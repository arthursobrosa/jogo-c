
#include <stdlib.h>
#include "jogador.h"
#define NUM_LINHAS 20
#define NUM_COLUNAS 80

typedef struct {
    bool menuAtivo;
    bool venceu;
    bool perdeu;
    //Caixa caixas[MAX_CAIXAS];
    int numCaixasAtivas;
}EstadoJogo; //salvar as info importantes


void exibirMenu( EstadoJogo *estado, char *caminhoArquivo, char mapaChar[NUM_LINHAS][NUM_COLUNAS], Jogador *voce, Jogador *inimigo);
void salvarJogo(Jogador *voce, Jogador *inimigo);
void carregarJogo(Jogador *voce, Jogador *inimigo);

void lerMapa(char *caminhoArquivo,char mapaChar[NUM_LINHAS][NUM_COLUNAS],Jogador *voce,Jogador *inimigo);

void desenharMapa(char mapaChar[NUM_LINHAS][NUM_COLUNAS], Celula mapaCel[NUM_LINHAS][NUM_COLUNAS]);
void _desenharCelulaMapa(int linha, int coluna, char c, Celula mapaCel[NUM_LINHAS][NUM_COLUNAS]);
//void desenharCaixas(EstadoJogo *estado);
void desenharRodape(float largura, float altura);

bool _ehLinhaChegada(Celula celula);
bool estaNaLinhaDeChegada(Celula mapaCel[NUM_LINHAS][NUM_COLUNAS], Jogador *jogador);
void VerificarLinhaChegada(Jogador *jogador,Celula mapaCel[NUM_LINHAS][NUM_COLUNAS],EstadoJogo *estado);

void desenharInformacoes(Jogador *voce, Jogador *inimigo);

void _obterCantosRetanguloRotacionado(Rectangle retangulo,float rotacao,Vector2 anchor,Vector2 saida[4]);
void _obterAABBdosCantos(const Vector2 cantos[4],Rectangle *aabb);

void _projetarPoligono(const Vector2 cantos[4], const Vector2 eixo, float *limiteMinimo, float *limiteMaximo);

bool _intervalosSeSobrepoem(float minA, float maxA, float minB, float maxB);

bool _satRetRet(const Vector2 a[4], const Vector2 b[4]);

bool _ehParede(Celula celula);
bool temParede(Celula mapaCel[NUM_LINHAS][NUM_COLUNAS], Jogador *jogador);

void exibirVitoria(EstadoJogo *estado);
void exibirGameOver(EstadoJogo *estado);
