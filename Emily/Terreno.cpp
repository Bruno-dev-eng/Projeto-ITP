#include "Terreno.h"
#include <cstdlib>
#include <ctime>
#include <cmath> 

// Aloca a matriz dinamicamente e inicializa o gerador de números aleatórios
Terreno::Terreno(int n) {
    // O algoritmo Diamond-Square exige que a matriz seja quadrada e de tamanho (2^N + 1)
    // ex: se n = 3, tamanho = 2^3 + 1 = 9 (matriz 9x9)
    this->tamanho = std::pow(2, n) + 1;

    // Aloca o vetor principal que guardará os ponteiros para cada linha
    altitudes = new double*[this->tamanho];
    
    // Aloca as colunas para cada linha e inicializa o terreno plano (0.0)
    for (int i = 0; i < this->tamanho; i++) {
        altitudes[i] = new double[this->tamanho];

        for (int j = 0; j < this->tamanho; j++) {
            altitudes[i][j] = 0.0; 
        }
    }
    
    // Inicializa a seed do gerador de números aleatórios (rand)
    // O uso do 'static' garante que a semente só seja definida UMA vez em toda a execução do programa
    static bool sementeInicializada = false;
    if (!sementeInicializada) {
        std::srand(std::time(nullptr));
        sementeInicializada = true;
    }
}


Terreno::~Terreno() {
    // Libera cada uma das linhas alocadas
    for (int i = 0; i < this->tamanho; i++) {
        delete[] altitudes[i];
    }
    // Libera o vetor de ponteiros principal
    delete[] altitudes;
}


bool Terreno::posicaoValida(int linha, int coluna) const {
    return (linha >= 0 && linha < tamanho && coluna >= 0 && coluna < tamanho);
}


// Gera um número real aleatório entre [-deslocamento, +deslocamento]
double obterDeslocamentoAleatorio(double deslocamento) {
    if (deslocamento <= 0) return 0.0;
    
    // std::rand() / RAND_MAX gera um valor entre 0.0 e 1.0
    double r = (double)std::rand() / RAND_MAX;
    
    // Transforma o intervalo [0, 1] para [-1, 1] e multiplica pelo fator de deslocamento
    return (r * 2.0 - 1.0) * deslocamento;
}


// ETAPA DIAMOND 
// Calcula o centro de um quadrado com base nos seus 4 cantos
void Terreno::etapaDiamond(int x, int y, int metade, double deslocamento) {
    // Coleta a altitude das 4 extremidades do quadrado atual
    double soma = altitudes[x - metade][y - metade] + // Canto Superior Esquerdo
                  altitudes[x - metade][y + metade] + // Canto Superior Direito
                  altitudes[x + metade][y - metade] + // Canto Inferior Esquerdo
                  altitudes[x + metade][y + metade];  // Canto Inferior Direito
    
    // O ponto central (x, y) recebe a média dos cantos + uma perturbação aleatória
    altitudes[x][y] = (soma / 4.0) + obterDeslocamentoAleatorio(deslocamento);
}


// ETAPA SQUARE
// Calcula os pontos médios das arestas olhando para os vizinhos em formato de cruz
void Terreno::etapaSquare(int x, int y, int metade, double deslocamento) {
    double soma = 0.0;
    int contagem = 0; // Conta quantos vizinhos são válidos 

    // Vizinho de CIMA
    if (posicaoValida(x - metade, y)) {
        soma += altitudes[x - metade][y];
        contagem++;
    }
    // Vizinho de BAIXO
    if (posicaoValida(x + metade, y)) {
        soma += altitudes[x + metade][y];
        contagem++;
    }
    // Vizinho da ESQUERDA
    if (posicaoValida(x, y - metade)) {
        soma += altitudes[x][y - metade];
        contagem++;
    }
    // Vizinho da DIREITA
    if (posicaoValida(x, y + metade)) {
        soma += altitudes[x][y + metade];
        contagem++;
    }

    // Calcula a média apenas dos vizinhos reais (serão 3 nas bordas e 4 no meio) + o ruído
    altitudes[x][y] = (soma / contagem) + obterDeslocamentoAleatorio(deslocamento);
}


// GERAR TERRENO
// Coordena os ciclos do algoritmo subdividindo o mapa progressivamente
void Terreno::gerarTerreno(double rugosidade) {
    // 1. Semeia os 4 cantos extremos do mapa com altitudes aleatórias iniciais (base: 100.0)
    altitudes[0][0] = obterDeslocamentoAleatorio(100.0);
    altitudes[0][tamanho - 1] = obterDeslocamentoAleatorio(100.0);
    altitudes[tamanho - 1][0] = obterDeslocamentoAleatorio(100.0);
    altitudes[tamanho - 1][tamanho - 1] = obterDeslocamentoAleatorio(100.0);

    // O 'passo' define o tamanho do bloco atual, começa preenchendo o mapa inteiro.
    int passo = tamanho - 1;
    double deslocamento = rugosidade;

    // O loop continua subdividindo os blocos até que o passo seja menor ou igual a 1 pixel
    while (passo > 1) {
        int metade = passo / 2;

        // SUB-ETAPA DIAMOND 
        // Varre a matriz pulando de bloco em bloco para encontrar os centros
        for (int x = metade; x < tamanho; x += passo) {
            for (int y = metade; y < tamanho; y += passo) {
                etapaDiamond(x, y, metade, deslocamento);
            }
        }

        // SUB-ETAPA SQUARE
        // Varre as linhas e colunas calculando os pontos médios das arestas
        for (int x = 0; x < tamanho; x += metade) {
            // O ponto inicial alterna para formar o padrão correto de grade intercalada
            int inicio = (x % passo == 0) ? metade : 0;
            for (int y = inicio; y < tamanho; y += passo) {
                etapaSquare(x, y, metade, deslocamento);
            }
        }

        // REDUÇÃO DO RUÍDO
        // À medida que os blocos ficam menores, reduzimos o deslocamento pela metade (0.5).
        // Isso faz com que grandes relevos surjam no início e pequenos detalhes/rugosidades no final.
        deslocamento *= 0.5; 
        
        // Reduz o tamanho do passo para a próxima iteração focar em sub-quadrados menores
        passo /= 2;
    }
}