#include "jogador.h"

void configurarJogadores(Jogador *voce, Jogador *inimigo)
{
    float largura = 2.5;
    float altura = 1;

    voce->celula.retangulo.width = largura;
    voce->celula.retangulo.height = altura;
    voce->celula.ancoraRotacao = (Vector2){0.5, 0.5};
    voce->celula.cor = BLUE;
    voce->velocidade = (Vector2){0};
    voce->velocidadeFutura = (Vector2){0};

    inimigo->celula.retangulo.width = largura;
    inimigo->celula.retangulo.height = altura;
    inimigo->celula.ancoraRotacao = (Vector2){0.5, 0.5};
    inimigo->celula.cor = RED;
    inimigo->velocidade = (Vector2){0};
    inimigo->velocidadeFutura = (Vector2){0};
}

void desenharJogador(Jogador *jogador)
{
    desenharCelula(jogador->celula);
}

void lidarComTecla(Jogador *jogador)
{
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        _avancar(jogador);
    }
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        _voltar(jogador);
    }
    else
    {
        _frear(jogador);
    }

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        _girar(jogador, false);
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        _girar(jogador, true);
    }
}

float _modulo(Vector2 vetor)
{
    return sqrt(pow(vetor.x, 2) + pow(vetor.y, 2));
}

Vector2 _normalizar(Vector2 vetor)
{
    float modulo = _modulo(vetor);

    if (modulo == 0)
    {
        return (Vector2){0};
    }

    return (Vector2){vetor.x / modulo, vetor.y / modulo};
}

void _acelerar(Jogador *jogador, bool praFrente)
{
    float deltaTempo = GetFrameTime();

    float angulo = jogador->celula.anguloFuturo * (M_PI / 180.0);
    Vector2 direcao = {cos(angulo), sin(angulo)};

    float aceleracaoReal = ACELERACAO * deltaTempo;
    if (!praFrente) aceleracaoReal *= -1;

    jogador->velocidadeFutura.x += direcao.x * aceleracaoReal;
    jogador->velocidadeFutura.y += direcao.y * aceleracaoReal;

    float velocidadeAtual = _modulo(jogador->velocidadeFutura);

    if (velocidadeAtual > VELOCIDADE_MAXIMA)
    {
        Vector2 normalizado = _normalizar(jogador->velocidadeFutura);
        jogador->velocidadeFutura.x = normalizado.x * VELOCIDADE_MAXIMA;
        jogador->velocidadeFutura.y = normalizado.y * VELOCIDADE_MAXIMA;
    }
}

void _avancar(Jogador *jogador)
{
    _acelerar(jogador, true);
    _mover(jogador);
}

void _voltar(Jogador *jogador)
{
    _acelerar(jogador, false);
    _mover(jogador);
}

void _frear(Jogador *jogador)
{
    float deltaTempo = GetFrameTime();
    float frenagem = ACELERACAO * deltaTempo;

    float moduloVelocidade = _modulo(jogador->velocidade);

    if (moduloVelocidade > 0)
    {
        float novoModuloVelocidade = moduloVelocidade - frenagem;
        if (novoModuloVelocidade < 0) novoModuloVelocidade = 0;

        float fator = (moduloVelocidade == 0) ? 0 : (novoModuloVelocidade / moduloVelocidade);

        jogador->velocidadeFutura.x = jogador->velocidade.x * fator;
        jogador->velocidadeFutura.y = jogador->velocidade.y * fator;
    }

    _mover(jogador);
}

void _girar(Jogador *jogador, bool sentidoHorario)
{
    float rotacao = 120.0f * GetFrameTime();
    if (!sentidoHorario) rotacao = -rotacao;

    float novoAngulo = jogador->celula.anguloFuturo + rotacao;

    novoAngulo = fmod(novoAngulo, 360.0f);
    if (novoAngulo < 0) novoAngulo += 360.0f;

    jogador->celula.anguloFuturo = novoAngulo;
}

void _mover(Jogador *jogador)
{
    float deltaTempo = GetFrameTime();

    jogador->celula.posicaoFutura.x =
        jogador->celula.retangulo.x + jogador->velocidadeFutura.x * deltaTempo;

    jogador->celula.posicaoFutura.y =
        jogador->celula.retangulo.y + jogador->velocidadeFutura.y * deltaTempo;
}

void atualizarJogador(Jogador *jogador)
{
    jogador->celula.retangulo.x = jogador->celula.posicaoFutura.x;
    jogador->celula.retangulo.y = jogador->celula.posicaoFutura.y;
    jogador->celula.angulo = jogador->celula.anguloFuturo;
    jogador->velocidade = jogador->velocidadeFutura;
}

void resetarJogador(Jogador *jogador)
{
    Vector2 velocidade = jogador->velocidadeFutura;
    Vector2 normal = {0,0};

    if (fabs(velocidade.x) > fabs(velocidade.y)) {
        normal.x = (velocidade.x > 0) ? -1 : 1;
        normal.y = 0;
    } else {
        normal.x = 0;
        normal.y = (velocidade.y > 0) ? -1 : 1;
    }

    float produtoEscalar = velocidade.x * normal.x + velocidade.y * normal.y;
    Vector2 refletida;
    refletida.x = velocidade.x - 2 * produtoEscalar * normal.x;
    refletida.y = velocidade.y - 2 * produtoEscalar * normal.y;

    refletida.x *= 0.2f;
    refletida.y *= 0.2f;

    jogador->velocidade = refletida;
    jogador->velocidadeFutura = refletida;

    jogador->celula.posicaoFutura.x = jogador->celula.retangulo.x;
    jogador->celula.posicaoFutura.y = jogador->celula.retangulo.y;

    jogador->celula.anguloFuturo = jogador->celula.angulo;
}
//void passouChegada (EstadoJogo *estado, Jogador *voce, Jogador *inimigo) {T}

/*int vida(Jogador *voce, Jogador *inimigo) {
    voce->vida=100;
    inimigo->vida=100;
}*/
