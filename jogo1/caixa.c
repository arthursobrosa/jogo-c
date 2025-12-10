//nao funciona ianda
/*
#include "caixa.h"

int SortearItem() {
    int item = (rand() % 4) + 1;
    return item;
}

void RealocarCaixa(Caixa *caixa, Vector2 novaPosicao) {
    caixa->posicao = novaPosicao;
    caixa->itemContido = SortearItem(); // Sorteia o novo item
    caixa->ativa = true;
}

// Função que verifica a colisão e coleta de uma caixa
void VerificarColeta(Jogador *jogador, Caixa *caixa, int numCaixas) {
    for (int i = 0; i < numCaixas; i++) {
        if (caixa[i].ativa) {
            if (CheckCollisionPointCircle(jogador->posicao, caixa[i].posicao, 10.0f)) {
                if (jogador->inventario == ITEM_NULO) {
                    jogador->inventario = caixa[i].itemContido;
                    if (jogador->inventario == ITEM_BONUS_VELOCIDADE) {
                        jogador->tempoBonusVelocidade = CONST_DURACAO_BONUS;
                        jogador->inventario = ITEM_NULO;
                    }
                    Vector2 novaPosicao = EncontrarPosicaoLivreNoMapa();
                    RealocarCaixa(&caixa[i], novaPosicao);
                }
            }
        }
    }
}

// Função que gerencia o uso do item do inventário do carro
void UsarItem(Jogador *jogador) {
    if (IsKeyPressed(KEY_SPACE)) {

        switch (jogador->inventario) {
            case ITEM_ARMA:
                CriarProjetil(jogador->posicao, jogador->angulo);
                jogador->inventario = ITEM_NULO;
                break;

            case ITEM_ESCUDO:
                // Implementação da Ação: Ativar Escudo
                if (!jogador->escudoAtivo) {
                    jogador->escudoAtivo = true;
                    jogador->tempoEscudo = CONST_DURACAO_ESCUDO;
                    jogador->inventario = ITEM_NULO;
                }
                break;

            case ITEM_BOMBA:
                Vector2 posBomba = CalcularPosicaoAntesDoCarro(jogador->posicao, jogador->angulo);
                CriarBomba(posBomba);

                jogaodr->inventario = ITEM_NULO;
                break;

            default:
                break;
        }
    }
}
// Atualiza os estados temporários (escudo e bônus de velocidade)
void AtualizarEfeitosTemporarios(Jogador *jogador, float deltaTempo) {


    if (jogador->escudoAtivo) {
        jogador->tempoEscudo -= deltaTempo;
        if (jogador->tempoEscudo <= 0.0f) {
            jogador->escudoAtivo = false;
        }
    }
    if (jogador->tempoBonusVelocidade > 0.0f) {
        jogador->tempoBonusVelocidade -= deltaTempo;

    }
}
// Lógica a ser chamada quando o carro sofreria 50 pontos de dano
void ReceberDano(Jogador *jogador, int dano) {
    if (dano != 50) {
        jogador->vida -= dano;
        jogador->velocidade = 0.0f;
        return;
    }

    // Se o escudo estiver ativo, absorve o dano de 50 pontos [cite: 147]
    if (jogador->escudoAtivo) {
        jogador->escudoAtivo = false;
        jogador->tempoEscudo = 0.0f;
    } else {
        jogador->vida -= dano;
        if (jogador->vida <= 0) {
            // Lógica de Fim de Jogo
        }
        jogador->velocidade = 0.0f;
        // Tocar som de dano/colisão [cite: 167]
    }
}
void CriarProjetil(Vector2 posjogador, float anguloJogador) {
    // Encontre o primeiro espaço livre no array de projéteis
    for (int i = 0; i < MAX_PROJETEIS; i++) {
        if (!projeteis[i].ativo) {
            const float VELOCIDADE_TIRO = 400.0f; // Exemplo em pixels/segundo

            projeteis[i].posicao = posJogaodr;
            projeteis[i].angulo = anguloJogador;
            projeteis[i].ativo = true;
            float anguloRad = anguloJogador * (PI / 180.0f);

            projeteis[i].velocidade.x = VELOCIDADE_TIRO * cosf(anguloRad);
            projeteis[i].velocidade.y = VELOCIDADE_TIRO * sinf(anguloRad);

            break;
        }
    }
}
void AtualizarProjeteis(float deltaTempo, Jogador *inimigos, int numInimigos) {
    for (int i = 0; i < MAX_PROJETEIS; i++) {
        if (projeteis[i].ativo) {
            projeteis[i].posicao.x += projeteis[i].velocidade.x * deltaTempo;
            projeteis[i].posicao.y += projeteis[i].velocidade.y * deltaTempo;
            for (int j = 0; j < numInimigos; j++) {
                if (CheckCollisionCircles(projeteis[i].posicao, 5.0f, inimigos[j].posicao, 15.0f)) {
                    ReceberDano(&inimigos[j], 50);
                    projeteis[i].ativo = false;
                    break;
                }
            }
            if (ColidiuComParede(projeteis[i].posicao)) {
                projeteis[i].ativo = false;
            }
        }
    }
}*/
