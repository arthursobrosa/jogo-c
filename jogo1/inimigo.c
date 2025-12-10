#include "inimigo.h"

void lidarComIA(Jogador *inimigo)
{
    float deltaTempo = GetFrameTime();
    // A IA sempre acelera para frente.
    _acelerar(inimigo, true);

    //  Lógica de Rotação Aleatória --
    if (inimigo->estaVirando)
    {
        // Decrementa o tempo restante da rotação atual
        inimigo->tempoRotacaoRestante -= deltaTempo;

        // Aplica o giro
        _girar(inimigo, inimigo->viraSentidoHorario);

        // Se o tempo acabar, para de virar
        if (inimigo->tempoRotacaoRestante <= 0.0f)
        {
            inimigo->estaVirando = false;
        }
    }
    else
    {
        // Se não estiver virando, verifica a chance de começar a virar
        if (((float)rand() / RAND_MAX) < PROBABILIDADE_ROTACAO_POR_FRAME)
        {
            // Inicia a rotação
            inimigo->estaVirando = true;

            // Define a duração aleatória
            inimigo->tempoRotacaoRestante = TEMPO_MIN_ROTACAO + ((float)rand() / RAND_MAX) * (TEMPO_MAX_ROTACAO - TEMPO_MIN_ROTACAO);

            // Define o sentido (50% de chance para cada lado)
            inimigo->viraSentidoHorario = (rand() % 2 == 0);
        }
    }

    // --- 3. Uso de Itens ---
    // Chama a lógica para decidir se o inimigo deve usar um item coletado.
    //GerenciarUsoItemIA(inimigo);

    // --- 4. Movimentação ---
    // Como a lógica de aceleração já foi aplicada, move o carro.
    _mover(inimigo);
}
