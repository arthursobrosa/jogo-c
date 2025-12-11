/*#include "caixa.h"
#include "janela.h"
#include <stdlib.h>
void ColetarItem(Jogador *jogador, EstadoJogo *estado)
{
    if (jogador->inventario != ITEM_NULO) return;


    Vector2 centroCarro = {
        jogador->celula.retangulo.x + jogador->celula.retangulo.width / 2,
        jogador->celula.retangulo.y + jogador->celula.retangulo.height / 2
    };

    for (int i = 0; i < estado->numCaixasAtivas; i++)
    {
        Caixa *caixa = &estado->caixas[i];

        if (caixa->ativo)
        {
            if (CheckCollisionPointRec(centroCarro, (Rectangle){caixa->posicao.x - 0.5f, caixa->posicao.y - 0.5f, 1.0f, 1.0f}))
            {
                caixa->ativo = false; // Desativa a caixa

                jogador->inventario = (TipoItem)GetRandomValue(ITEM_ARMA, ITEM_BONUS_VELOCIDADE);
                if (jogador->inventario == ITEM_BONUS_VELOCIDADE) {
                    jogador->tempoVelocidade = CONST_DURACAO_BONUS;
                    jogador->inventario = ITEM_NULO; // Consome na hora
                }

                break;
            }
        }
    }
}

// --- 2. FUNÇÃO DE USO DE ITEM ---

void UsarItem(Jogador *jogador, EstadoJogo *estado)
{
    if (jogador->inventario == ITEM_NULO) return;

    switch (jogador->inventario)
    {
        case ITEM_ARMA:
            // CriarProjetil(jogador->celula.retangulo, jogador->celula.angulo);
            break;

        case ITEM_ESCUDO:
            jogador->escudoAtivo = true;
            jogador->tempoEscudo = CONST_DURACAO_ESCUDO;
            break;

        case ITEM_BOMBA:
            // CriarBomba(CalcularPosicaoRetaguarda(jogador->celula.retangulo, jogador->celula.angulo));
            break;

        default:
            break;
    }

    jogador->inventario = ITEM_NULO; // Consome o item
}

// --- 3. FUNÇÃO DE GESTÃO DE EFEITOS TEMPORÁRIOS ---

void GerenciarEfeitosTemporarios(Jogador *jogador, float deltaTempo)
{
    // Gerencia o escudo
    if (jogador->escudoAtivo) {
        jogador->tempoEscudo -= deltaTempo;
        if (jogador->tempoEscudo <= 0.0f) {
            jogador->escudoAtivo = false;
        }
    }

    // Gerencia o bônus de velocidade (se for um efeito que dura)
    if (jogador->tempoVelocidade > 0.0f) {
        jogador->tempoVelocidade -= deltaTempo;
        // NOTE: A lógica de física real deve usar o tempoVelocidade para aplicar um bônus à VELOCIDADE_MAXIMA
    }
}


// --- 4. FUNÇÃO DE DESENHO ---

void desenharCaixas(EstadoJogo *estado)
{
    // Assumimos que ESCALA está definido em celula.h
    extern const float ESCALA;

    for (int i = 0; i < estado->numCaixasAtivas; i++)
    {
        if (estado->caixas[i].ativo)
        {
            DrawRectangle(
                (int)(estado->caixas[i].posicao.x * ESCALA - 8),
                (int)(estado->caixas[i].posicao.y * ESCALA - 8),
                16,
                16,
                ORANGE
            );
        }
    }
}*/
