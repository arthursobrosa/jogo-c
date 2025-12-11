#include "inimigo.h"
// --- Implementação da Função de Verificação de Parede ---
bool VerificarParedeProxima(
    char mapaChar[NUM_LINHAS][NUM_COLUNAS],
    float angulo,
    int linhaAtual,
    int colunaAtual
)
{
    float anguloRad = angulo * (M_PI / 180.0);
    float deltaX = DISTANCIA_VERIFICACAO * cos(anguloRad);
    float deltaY = DISTANCIA_VERIFICACAO * sin(anguloRad);
    float posVerificacaoX = (float)colunaAtual + deltaX;
    float posVerificacaoY = (float)linhaAtual + deltaY;

    int linhaAlvo = (int)roundf(posVerificacaoY);
    int colunaAlvo = (int)roundf(posVerificacaoX);

    if (linhaAlvo < 0 || linhaAlvo >= NUM_LINHAS || colunaAlvo < 0 || colunaAlvo >= NUM_COLUNAS)
    {
        return true; // Limite do mapa é considerado Parede
    }

    char celulaAlvo = mapaChar[linhaAlvo][colunaAlvo];

    if (celulaAlvo == 'P' || celulaAlvo == 'p')
    {
        return true; // Parede detectada
    }
    return false;
}


void lidarComIA(Jogador *inimigo, Jogador *jogador, char mapaChar[NUM_LINHAS][NUM_COLUNAS])
{
    float deltaTempo = GetFrameTime();

    // 1. Atualização do Temporizador
    inimigo->tempoDesdeSpawn += deltaTempo;

    // 2. Detecção de Posição e Parede
    int linhaAtual = (int)floorf(inimigo->celula.retangulo.y);
    int colunaAtual = (int)floorf(inimigo->celula.retangulo.x);

    bool paredeProxima = VerificarParedeProxima(mapaChar, inimigo->celula.anguloFuturo, linhaAtual, colunaAtual);

    // --- LÓGICA DE REVERSO (Prioridade Máxima) ---

    // A. INICIA A RÉ: Se parede detectada E não estiver em modo de desprendimento
    if (paredeProxima && !inimigo->estaVirando) {
        // Usa estaVirando para sinalizar o modo de desprendimento (Ré)
        inimigo->estaVirando = true;
        inimigo->tempoRotacaoRestante = TEMPO_REVERSO;
        inimigo->viraSentidoHorario = (rand() % 2 == 0); // Define o lado do giro para descolar
    }

    // B. EXECUÇÃO DA RÉ/GIRO DE EMERGÊNCIA
    if (inimigo->estaVirando && paredeProxima)
    {
        // Se ainda está na área de perigo (parede próxima) ou no ciclo de TEMPO_REVERSO

        inimigo->tempoRotacaoRestante -= deltaTempo;

        // MOVIMENTO: Dá ré (praFrente=false, chama _voltar)
        _acelerar(inimigo, false);

        // ROTAÇÃO: Força o giro para descolar
        _girar(inimigo, inimigo->viraSentidoHorario);

        if (inimigo->tempoRotacaoRestante <= 0.0f) {
            inimigo->estaVirando = false; // Finaliza o modo de desprendimento
        }
    }
    else
    {
        // --- LÓGICA NORMAL (SE NENHUM PERIGO E NÃO DANDO RÉ) ---

        // 1. Aceleração para frente (Movimento principal)
        _acelerar(inimigo, true);

        // 2. Giro Aleatório (Apenas se o delay inicial tiver passado)
        if (!inimigo->estaVirando && inimigo->tempoDesdeSpawn > 0.5f)
        {
            if (((float)rand() / RAND_MAX) < PROBABILIDADE_ROTACAO_POR_FRAME) {
                inimigo->estaVirando = true;
                inimigo->tempoRotacaoRestante = TEMPO_MIN_ROTACAO + ((float)rand() / RAND_MAX) * (TEMPO_MAX_ROTACAO - TEMPO_MIN_ROTACAO);
                inimigo->viraSentidoHorario = (rand() % 2 == 0);
            }
        }
        else if (inimigo->estaVirando && inimigo->tempoRotacaoRestante > 0.0f)
        {
             // Continua giro aleatório
             inimigo->tempoRotacaoRestante -= deltaTempo;
             _girar(inimigo, inimigo->viraSentidoHorario);
             if (inimigo->tempoRotacaoRestante <= 0.0f) inimigo->estaVirando = false;
        }
    }

    // Movimentação Final (aplica o resultado de _acelerar/frear)
    _mover(inimigo);
}
