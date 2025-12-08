#include "janela.h"

void lerMapa
(
    char *caminhoArquivo, 
    char mapaChar[NUM_LINHAS][NUM_COLUNAS], 
    Jogador *voce, 
    Jogador *inimigo
)
{
    FILE *arquivo = fopen(caminhoArquivo, "r");

    if (!arquivo) 
    {
        printf("Erro ao abrir arquivo do mapa!\n");
        return;
    }

    char linhaDeTexto[100];

    for (int linha = 0; linha < NUM_LINHAS; linha++) 
    {
        fgets(linhaDeTexto, sizeof(linhaDeTexto), arquivo);

        for (int coluna = 0; coluna < NUM_COLUNAS; coluna++) 
        {
            char c = linhaDeTexto[coluna];

            if (c == 'j')
            {
                voce->celula.retangulo.x = coluna;
                voce->celula.retangulo.y = linha;
                voce->celula.posicaoFutura.x = voce->celula.retangulo.x;
                voce->celula.posicaoFutura.y = voce->celula.retangulo.y;
            }

            if (c == 'i')
            {
                inimigo->celula.retangulo.x = coluna;
                inimigo->celula.retangulo.y = linha;
                inimigo->celula.posicaoFutura.x = inimigo->celula.retangulo.x;
                inimigo->celula.posicaoFutura.y = inimigo->celula.retangulo.y;
            }

            mapaChar[linha][coluna] = c;
        }
    }

    fclose(arquivo);
}

void desenharMapa
(
    char mapaChar[NUM_LINHAS][NUM_COLUNAS], 
    Celula mapaCel[NUM_LINHAS][NUM_COLUNAS]
)
{
    for (int linha = 0; linha < NUM_LINHAS; linha++)
    {
        for (int coluna = 0; coluna < NUM_COLUNAS; coluna++)
        {
            _desenharCelulaMapa(
                linha, 
                coluna, 
                mapaChar[linha][coluna],
                mapaCel
            );
        }
    }
}

void _desenharCelulaMapa
(
    int linha, 
    int coluna, 
    char c,
    Celula mapaCel[NUM_LINHAS][NUM_COLUNAS]
)
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
    celula.ancoraRotacao = (Vector2){0,0};
    celula.angulo = 0;

    mapaCel[linha][coluna] = celula;
    desenharCelula(celula);
}

void desenharRodape(float largura, float altura)
{
    Celula celula;
    celula.retangulo.x = 0;
    celula.retangulo.y = (float)NUM_LINHAS;
    celula.retangulo.width = largura;
    celula.retangulo.height = altura;
    celula.ancoraRotacao = (Vector2){0,0};
    celula.angulo = 0;
    celula.cor = YELLOW;

    desenharCelula(celula);
}

void _obterCantosRetanguloRotacionado
(
    Rectangle retangulo,
    float rotacao,
    Vector2 anchor,
    Vector2 saida[4]
)
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

void _obterAABBdosCantos
(
    const Vector2 cantos[4], 
    Rectangle *aabb
)
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

void _projetarPoligono
(
    const Vector2 cantos[4],
    const Vector2 eixo,
    float *limiteMinimo,
    float *limiteMaximo
)
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

bool _intervalosSeSobrepoem
(
    float minA,
    float maxA,
    float minB,
    float maxB
)
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
        Vector2 eixoProjetado = (Vector2){-eixo.y, eixo.x};

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

bool temParede(
    Celula mapaCel[NUM_LINHAS][NUM_COLUNAS],
    Jogador *jogador
)
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
            cantosCelula[0] = (Vector2){celula.retangulo.x, celula.retangulo.y};
            cantosCelula[1] = (Vector2){celula.retangulo.x + celula.retangulo.width, celula.retangulo.y};
            cantosCelula[2] = (Vector2){celula.retangulo.x + celula.retangulo.width, celula.retangulo.y + celula.retangulo.height};
            cantosCelula[3] = (Vector2){celula.retangulo.x, celula.retangulo.y + celula.retangulo.height};

            if (_satRetRet(cantosJogador, cantosCelula)) return true;
        }
    }

    return false;
}