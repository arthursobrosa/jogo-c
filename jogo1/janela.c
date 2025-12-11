
#include "janela.h"


void exibirMenu(EstadoJogo *estado, char *caminhoArquivo, char mapaChar[NUM_LINHAS][NUM_COLUNAS], Jogador *voce, Jogador *inimigo)
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    DrawText("Menu Principal",  100,50,40,WHITE);
    DrawText("(N) Novo Jogo", 100,100,20,WHITE);
    DrawText("(C) Carregar Jogo",  100,150,20,WHITE);
    DrawText("(S) Salvar Jogo",  100,200,20,WHITE);
    DrawText("(Q) Sair",  100,250,20,WHITE);
    DrawText("(V) Voltar ao Jogo",  100,300,20,WHITE);
    DrawText("(Tab) Pausar",  100,350,20,WHITE);

    EndDrawing();
    //Reinicia tudo
    if (IsKeyPressed(KEY_N))
    {
        estado->menuAtivo = false;
        lerMapa(caminhoArquivo, mapaChar, voce, inimigo);
        voce->vida=100;
        inimigo->vida=100;
        voce->voltas=0;
        inimigo->voltas=0;
        //Jogador->caixa.item=ITEM_NULO
        estado->venceu = false;
        estado->perdeu = false;
    }
    //carrega o njogo
    if (IsKeyPressed(KEY_C))
    {
        carregarJogo(voce, inimigo);
        estado->menuAtivo = false;
    }
    //salva o jogo
    if (IsKeyPressed(KEY_S))
    {
        salvarJogo(voce, inimigo);
    }
    //fecah o jogo
    if (IsKeyPressed(KEY_Q))
    {
        CloseWindow();
        exit(0);
    }
    if (IsKeyPressed(KEY_V))
    {
        estado->menuAtivo = false;
    }
}
//salva e carrega o arq binario do game
void salvarJogo(Jogador *voce, Jogador *inimigo)
{
    FILE *arq = fopen("jogosalvo.bin","wb");
    if (!arq)
    {
        printf("Erro ao salvar o jogo!\n");
        return;
    }
    fwrite(voce,sizeof(Jogador),1,arq);
    fwrite(inimigo,sizeof(Jogador),1,arq);
    fclose(arq);
    printf("Jogo salvo com sucesso!\n");
}
void carregarJogo(Jogador *voce, Jogador *inimigo)
{
    FILE *arq = fopen("jogosalvo.bin","rb");
    if (!arq)
    {
        printf("Nenhum jogo salvo encontrado!\n");
        return;
    }
    fread(voce,sizeof(Jogador),1,arq);
    fread(inimigo,sizeof(Jogador),1,arq);
    fclose(arq);
    printf("Jogo carregado com sucesso!\n");
}

void lerMapa(char *caminhoArq, char mapaChar[NUM_LINHAS][NUM_COLUNAS], Jogador *voce, Jogador *inimigo)
{
    FILE *arq = fopen(caminhoArq, "r");

    if (!arq)
    {
        printf("Erro ao abrir arquivo do mapa!\n");
        return;
    }

    char linhaDeTexto[100];

    for (int linha = 0; linha < NUM_LINHAS; linha++)
    {
        fgets(linhaDeTexto, sizeof(linhaDeTexto), arq);

        for (int coluna = 0; coluna < NUM_COLUNAS; coluna++)
        {

            char c = linhaDeTexto[coluna];

            /*if (c == 'C' && contadorCaixas < MAX_CAIXAS)
            {
                // Localiza a caixa e preenche a struct Caixa
                estado->caixas[contadorCaixas].id = contadorCaixas;
                estado->caixas[contadorCaixas].posicao = (Vector2){(float)coluna + 0.5f, (float)linha + 0.5f}; // Centro da célula
                estado->caixas[contadorCaixas].ativo = true;
                contadorCaixas++;
            }*/

            if (c == 'j')
            {
                voce->celula.retangulo.x = coluna;
                voce->celula.retangulo.y = linha + 0.2;
                voce->celula.posicaoFutura.x = voce->celula.retangulo.x;
                voce->celula.posicaoFutura.y = voce->celula.retangulo.y;
            }
            if (c == 'i')
            {
                inimigo->celula.retangulo.x = coluna;
                inimigo->celula.retangulo.y = linha - 0.2;
                inimigo->celula.posicaoFutura.x = inimigo->celula.retangulo.x;
                inimigo->celula.posicaoFutura.y = inimigo->celula.retangulo.y;
            }
            mapaChar[linha][coluna] = c;
        }
    }
    fclose(arq);
}

void desenharMapa (char mapaChar[NUM_LINHAS][NUM_COLUNAS],Celula mapaCel[NUM_LINHAS][NUM_COLUNAS])
{
    for (int linha = 0; linha < NUM_LINHAS; linha++)
    {
        for (int coluna = 0; coluna < NUM_COLUNAS; coluna++)
        {
            _desenharCelulaMapa(
                linha,
                coluna,
                mapaChar[linha][coluna],
                mapaCel);
        }
    }
}

void _desenharCelulaMapa(int linha, int coluna, char c, Celula mapaCel[NUM_LINHAS][NUM_COLUNAS])
{

    Celula celula;
    celula.retangulo.x = coluna;
    celula.retangulo.y = linha;
    celula.retangulo.width = 1;
    celula.retangulo.height = 1;
    Color cor;
    switch (c)
    {
    case 'p':
        cor = BROWN;
        break;
    case 'L':
        cor = PINK;
        break;
    default:
        cor = WHITE;
    }

    celula.cor = cor;
    celula.ancoraRotacao = (Vector2)
    {
        0,0
    };
    celula.angulo = 0;

    mapaCel[linha][coluna] = celula;
    desenharCelula(celula);
}
/*void desenharCaixas(EstadoJogo *estado)
{
    for (int i = 0; i < estado->numCaixasAtivas; i++)
    {
        if (estado->caixas[i].ativo)
        {
            // Desenha um retângulo simples (amarelo ou branco) no centro da posição da caixa
            DrawRectangle(
                (int)(estado->caixas[i].posicao.x * ESCALA - 8), // Centraliza usando ESCALA
                (int)(estado->caixas[i].posicao.y * ESCALA - 8),
                16, // Tamanho
                16,
                ORANGE // Cor da caixa de item
            );
        }
    }
}*/
/*void ColetarItem(Jogador *jogador, EstadoJogo *estado)
{
    if (jogador->inventario != ITEM_NULO) return; // Não coleta se já tiver item

    // O centro do carro
    Vector2 centroCarro = {
        jogador->celula.retangulo.x + jogador->celula.retangulo.width / 2,
        jogador->celula.retangulo.y + jogador->celula.retangulo.height / 2
    };

    for (int i = 0; i < estado->numCaixasAtivas; i++)
    {
        Caixa *caixa = &estado->caixas[i];

        if (caixa->ativo)
        {
            // Verificação de colisão AABB simplificada (assumindo caixa 1x1 no centro)
            // Distância (no sistema de coordenadas do mapa)
            if (CheckCollisionPointRec(centroCarro, (Rectangle){caixa->posicao.x - 0.5f, caixa->posicao.y - 0.5f, 1.0f, 1.0f}))
            {
                // Item Coletado!
                caixa->ativo = false; // Desativa a caixa

                // Atribui um item aleatório (exceto ITEM_NULO)
                jogador->inventario = (TipoItem)GetRandomValue(ITEM_ARMA, ITEM_BONUS_VELOCIDADE);

                // Efeito imediato: Se for bônus de velocidade, ativa na hora.
                if (jogador->inventario == ITEM_BONUS_VELOCIDADE) {
                    // Implementar AtivarBonusVelocidade(jogador);
                }

                break;
            }
        }
    }
}*/

//faz a parte amarela do mapa embaixo
void desenharRodape(float largura, float altura)
{
    Celula celula;
    celula.retangulo.x = 0;
    celula.retangulo.y = (float)NUM_LINHAS;
    celula.retangulo.width = largura;
    celula.retangulo.height = altura;
    celula.ancoraRotacao = (Vector2)
    {
        0,0
    };
    celula.angulo = 0;
    celula.cor = YELLOW;


    desenharCelula(celula);
}

//Define o que a linha de chegada pela cor da cel do L
bool _ehLinhaChegada(Celula celula)
{
    Color corCelula = celula.cor;
    Color corLinha = PINK;

    // Compara todos os componentes de cor (RGB)
    return (corCelula.r == corLinha.r && corCelula.g == corLinha.g && corCelula.b == corLinha.b && corCelula.a == corLinha.a);
}

bool estaNaLinhaDeChegada(Celula mapaCel[NUM_LINHAS][NUM_COLUNAS], Jogador *jogador)
{
    Vector2 cantosJogador[4];
    // Usamos o retângulo ATUAL do jogador (sem a posição futura, pois é uma checagem de estado)
    Rectangle jogadorRetangulo = jogador->celula.retangulo;

    // Obtém os cantos rotacionados do carro.
    _obterCantosRetanguloRotacionado(
        jogadorRetangulo,
        jogador->celula.angulo, // Ângulo atual (não futuro)
        jogador->celula.ancoraRotacao,
        cantosJogador
    );

    // Obtém a Axis-Aligned Bounding Box (AABB) para otimizar a varredura do mapa.
    Rectangle aabbJogador;
    _obterAABBdosCantos(cantosJogador, &aabbJogador);

    // Converte as coordenadas da AABB para índices da matriz (assumindo TILE_UNIT=1)
    int inicioColuna = (int)floorf(aabbJogador.x);
    int inicioLinha = (int)floorf(aabbJogador.y);
    int fimColuna = (int)ceilf(aabbJogador.x + aabbJogador.width);
    int fimLinha = (int)ceilf(aabbJogador.y + aabbJogador.height);

    // Limites de segurança da matriz
    if (inicioColuna < 0) inicioColuna = 0;
    if (inicioLinha < 0) inicioLinha = 0;
    if (fimColuna >= NUM_COLUNAS) fimColuna = NUM_COLUNAS - 1;
    if (fimLinha >= NUM_LINHAS) fimLinha = NUM_LINHAS - 1;

    // Varre apenas as células que podem estar colidindo com o carro
    for (int i = inicioLinha; i <= fimLinha; i++)
    {
        for (int j = inicioColuna; j <= fimColuna; j++)
        {
            Celula celula = mapaCel[i][j];

            // Verifica se a célula é a Linha de Chegada
            if (!_ehLinhaChegada(celula)) continue;

            // Se a célula for 'L', verifica a colisão precisa (SAT)
            Vector2 cantosCelula[4];
            // As células do mapa são retângulos não rotacionados, 1x1
            cantosCelula[0] = (Vector2)
            {
                celula.retangulo.x, celula.retangulo.y
            };
            cantosCelula[1] = (Vector2)
            {
                celula.retangulo.x + 1, celula.retangulo.y
            };
            cantosCelula[2] = (Vector2)
            {
                celula.retangulo.x + 1, celula.retangulo.y + 1
            };
            cantosCelula[3] = (Vector2)
            {
                celula.retangulo.x, celula.retangulo.y + 1
            };

            if (_satRetRet(cantosJogador, cantosCelula))
            {
                return true; // Colisão detectada com a Linha de Chegada
            }
        }
    }
    return false;
}
void VerificarLinhaChegada(Jogador *jogador,Celula mapaCel[NUM_LINHAS][NUM_COLUNAS],EstadoJogo *estado)
{
    // Verifica se o carro está colidindo com a célula 'L' no frame atual
    bool colidiuComL = estaNaLinhaDeChegada(mapaCel, jogador);

    // --- Lógica de Contagem e Estado ---

    // 1. CONTAGEM DA VOLTA:
    // Se o carro está colidindo com 'L' E a contagem está liberada (podeContarVolta = true):
    if (colidiuComL && jogador->podeContarVolta)
    {
        // **VOLTA CONCLUÍDA**

        jogador->voltas++;
        jogador->podeContarVolta = false; // BLOQUEIA a contagem imediatamente

        // Exemplo de log para debug:
        // printf("Volta %d concluída por %s!\n", jogador->voltas, (jogador == &estado->voce) ? "Jogador" : "Inimigo");

        // --- Verificação de Vitória -
    }

    // 2. RESET (Libera a Contagem para a Próxima Volta):
    // Se o carro NÃO está colidindo com 'L' E a contagem estava BLOQUEADA:
    if (!colidiuComL && !jogador->podeContarVolta)
    {
        // O carro saiu da área 'L' e agora está na pista.
        // Libera a contagem para a próxima vez que ele entrar na linha de chegada.
        jogador->podeContarVolta = true;
    }


    // 2. RESET (Libera a Contagem):
    // Se o carro NÃO está colidindo com 'L' e a contagem estava BLOQUEADA:
    if (!colidiuComL && !jogador->podeContarVolta)
    {
        // O carro saiu da área 'L'. Libera a contagem para a próxima volta.
        jogador->podeContarVolta = true;
    }

    // NOTA: Esta abordagem não garante o sentido anti-horário (baixo para cima) exigido pelo trabalho.
    // Ela apenas garante que a volta é contada uma única vez, exigindo que o carro saia da área 'L' para resetar.
}

void desenharInformacoes(Jogador *voce, Jogador *inimigo)
{
    DrawText(TextFormat("Vida: %d", voce->vida), 10, 320, 20, BLACK);
    DrawText(TextFormat("Volta: %d", voce->voltas), 10, 340, 20, BLACK);
    DrawText(TextFormat("Vida inimigo: %d", inimigo->vida), 1100, 320, 20, BLACK);
    DrawText(TextFormat("Volta inimigo: %d", inimigo->voltas), 1100, 340, 20, BLACK);
}

void _obterCantosRetanguloRotacionado(Rectangle retangulo, float rotacao, Vector2 anchor, Vector2 saida[4])
{
    float metadeLargura = retangulo.width / 2;
    float metadeAltura = retangulo.height / 2;

    float centroX = retangulo.x + metadeLargura;
    float centroY = retangulo.y + metadeAltura;

    float offsetX = (anchor.x - 0.5f) * retangulo.width;
    float offsetY = (anchor.y - 0.5f) * retangulo.height;

    Vector2 topoEsquerda = {-metadeLargura - offsetX, -metadeAltura - offsetY};
    Vector2 topoDireita  = { metadeLargura - offsetX, -metadeAltura - offsetY};
    Vector2 baseDireita  = { metadeLargura - offsetX,  metadeAltura - offsetY};
    Vector2 baseEsquerda = {-metadeLargura - offsetX,  metadeAltura - offsetY};

    // relativos ao centro do retangulo
    Vector2 cantosLocais[4] =
    {
        topoEsquerda,
        topoDireita,
        baseDireita,
        baseEsquerda
    };

    float rotacaoRadianos = rotacao * (M_PI / 180);
    float seno = sin(rotacaoRadianos);
    float cosseno = cos(rotacaoRadianos);

    for (int i = 0; i < 4; i++)
    {
        float xRotacionado = cantosLocais[i].x * cosseno - cantosLocais[i].y * seno;
        float yRotacionado = cantosLocais[i].x * seno + cantosLocais[i].y * cosseno;
        saida[i].x = centroX + xRotacionado;
        saida[i].y = centroY + yRotacionado;
    }
}

void _obterAABBdosCantos(const Vector2 cantos[4], Rectangle *aabb)
{
    float minX = cantos[0].x;
    float maxX = cantos[0].x;
    float minY = cantos[0].y;
    float maxY = cantos[0].y;

    for (int i = 0; i < 4; i++)
    {
        if (cantos[i].x < minX) minX = cantos[i].x;
        if (cantos[i].x > maxX) maxX = cantos[i].x;
        if (cantos[i].y < minY) minY = cantos[i].y;
        if (cantos[i].y > maxY) maxY = cantos[i].y;
    }
    aabb->x = minX;
    aabb->y = minY;
    aabb->width = maxX - minX;
    aabb->height = maxY - minY;
}

void _projetarPoligono(const Vector2 cantos[4], const Vector2 eixo, float *limiteMinimo, float *limiteMaximo)
{
    float produtoEscalar = cantos[0].x * eixo.x + cantos[0].y * eixo.y;
    float min = produtoEscalar;
    float max = produtoEscalar;

    for (int i = 0; i < 4; i++)
    {
        produtoEscalar = cantos[i].x * eixo.x + cantos[i].y * eixo.y;
        if (produtoEscalar < min) min = produtoEscalar;
        if (produtoEscalar > max) max = produtoEscalar;
    }
    *limiteMinimo = min;
    *limiteMaximo = max;
}
bool _intervalosSeSobrepoem(float minA, float maxA, float minB, float maxB)
{
    return !(maxA < minB || maxB < minA);
}
bool _satRetRet(const Vector2 a[4], const Vector2 b[4])
{
    Vector2 eixos[4];
    eixos[0] = (Vector2)
    {
        a[1].x - a[0].x,
        a[1].y - a[0].y
    };
    eixos[1] = (Vector2)
    {
        a[2].x - a[1].x,
        a[2].y - a[1].y
    };
    eixos[2] = (Vector2)
    {
        b[1].x - b[0].x,
        b[1].y - b[0].y
    };
    eixos[3] = (Vector2)
    {
        b[2].x - b[1].x,
        b[2].y - b[1].y
    };
    for (int i = 0; i < 4; i++)
    {
        Vector2 eixo = eixos[i];
        Vector2 eixoProjetado = (Vector2)
        {
            -eixo.y, eixo.x
            };

        float magnitude = sqrt(pow(eixoProjetado.x, 2) + pow(eixoProjetado.y, 2));
        if (magnitude == 0) continue;
        eixoProjetado.x /= magnitude;
        eixoProjetado.y /= magnitude;
        float minA, maxA, minB, maxB;
        _projetarPoligono(a, eixoProjetado, &minA, &maxA);
        _projetarPoligono(b, eixoProjetado, &minB, &maxB);
        if (!_intervalosSeSobrepoem(minA, maxA, minB, maxB)) return false;
    }
    return true;
}
bool _ehParede(Celula celula)
{
    Color corCelula = celula.cor;
    Color corMarrom = BROWN;

    return (corCelula.r == corMarrom.r && corCelula.g == corMarrom.g && corCelula.b == corMarrom.b && corCelula.a == corMarrom.a);
}

bool temParede(Celula mapaCel[NUM_LINHAS][NUM_COLUNAS], Jogador *jogador)
{
    Vector2 cantosJogador[4];
    Rectangle jogadorRetangulo = jogador->celula.retangulo;
    jogadorRetangulo.x = jogador->celula.posicaoFutura.x;
    jogadorRetangulo.y = jogador->celula.posicaoFutura.y;

    _obterCantosRetanguloRotacionado(
        jogadorRetangulo,
        jogador->celula.anguloFuturo,
        jogador->celula.ancoraRotacao,
        cantosJogador
    );

    Rectangle aabbJogador;
    _obterAABBdosCantos(cantosJogador, &aabbJogador);

    int inicioColuna = (int)floorf(aabbJogador.x / mapaCel[0][0].retangulo.width);
    int inicioLinha = (int)floorf(aabbJogador.y / mapaCel[0][0].retangulo.height);
    int fimColuna = (int)floorf((aabbJogador.x + aabbJogador.width) / mapaCel[0][0].retangulo.width);
    int fimLinha = (int)floorf((aabbJogador.y + aabbJogador.height) / mapaCel[0][0].retangulo.height);


    if (inicioColuna < 0) inicioColuna = 0;
    if (inicioLinha < 0) inicioLinha = 0;
    if (fimColuna >= NUM_COLUNAS) fimColuna = NUM_COLUNAS - 1;
    if (fimLinha >= NUM_LINHAS) fimLinha = NUM_LINHAS - 1;

    for (int i = inicioLinha; i <= fimLinha; i++)
    {
        for (int j = inicioColuna; j <= fimColuna; j++)
        {
            Celula celula = mapaCel[i][j];
            if (!_ehParede(celula)) continue;

            Vector2 cantosCelula[4];
            cantosCelula[0] = (Vector2)
            {
                celula.retangulo.x, celula.retangulo.y
            };
            cantosCelula[1] = (Vector2)
            {
                celula.retangulo.x + celula.retangulo.width, celula.retangulo.y
            };
            cantosCelula[2] = (Vector2)
            {
                celula.retangulo.x + celula.retangulo.width, celula.retangulo.y + celula.retangulo.height
            };
            cantosCelula[3] = (Vector2)
            {
                celula.retangulo.x, celula.retangulo.y + celula.retangulo.height
            };

            if (_satRetRet(cantosJogador, cantosCelula)) return true;
        }
    }
    return false;
}

//void cindicaoVD()
void exibirVitoria(EstadoJogo *estado)
{
    if (estado->venceu=true)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Voce venceu!", 200,200,50,YELLOW);
        EndDrawing();
    }
}
void exibirGameOver(EstadoJogo *estado)
{
    if(estado->perdeu=true)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Game Over!", 200,200,50,RED);
        EndDrawing();
    }
}
