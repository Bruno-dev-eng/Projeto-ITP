#include "Terreno.h"
#include <cstdlib>
#include <ctime>
#include <cmath> 

Terreno::Terreno(int n) {
    
  this->tamanho = std::pow(2, n) + 1;
    
  altitudes = new double*[this->tamanho];
  
  for (int i = 0; i < this->tamanho; i++) {
        
    altitudes[i] = new double[this->tamanho];

    for (int j = 0; j < this->tamanho; j++) { altitudes[i][j] = 0.0; }
    }
    
    static bool sementeInicializada = false;
    if (!sementeInicializada) { std::srand(std::time(nullptr)); sementeInicializada = true; }
}

Terreno::~Terreno() { for (int i = 0; i < this->tamanho; i++) {
        delete[] altitudes[i]; }
    delete[] altitudes; }

bool Terreno::posicaoValida(int linha, int coluna) const { return (linha >= 0 && linha < tamanho && coluna >= 0 && coluna < tamanho); }

double obterDeslocamentoAleatorio(double deslocamento) {
    if (deslocamento <= 0) return 0.0;

    double r = (double)std::rand() / RAND_MAX;
    
    return (r * 2.0 - 1.0) * deslocamento;
}

void Terreno::etapaDiamond(int x, int y, int metade, double deslocamento) {
    double soma = altitudes[x - metade][y - metade] +
                  altitudes[x - metade][y + metade] +
                  altitudes[x + metade][y - metade] +
                  altitudes[x + metade][y + metade];
    
    altitudes[x][y] = (soma / 4.0) + obterDeslocamentoAleatorio(deslocamento); }

void Terreno::etapaSquare(int x, int y, int metade, double deslocamento) {
    double soma = 0.0;
    int contagem = 0;

    if (posicaoValida(x - metade, y)) { soma += altitudes[x - metade][y]; contagem++; }
  
    if (posicaoValida(x + metade, y)) { soma += altitudes[x + metade][y]; contagem++; }
  
    if (posicaoValida(x, y - metade)) { soma += altitudes[x][y - metade]; contagem++; }
  
    if (posicaoValida(x, y + metade)) { soma += altitudes[x][y + metade]; contagem++; }

    altitudes[x][y] = (soma / contagem) + obterDeslocamentoAleatorio(deslocamento); }


void Terreno::gerarTerreno(double rugosidade) {

    altitudes[0][0] = obterDeslocamentoAleatorio(100.0);
    altitudes[0][tamanho - 1] = obterDeslocamentoAleatorio(100.0);
    altitudes[tamanho - 1][0] = obterDeslocamentoAleatorio(100.0);
    altitudes[tamanho - 1][tamanho - 1] = obterDeslocamentoAleatorio(100.0);

    int passo = tamanho - 1; double deslocamento = rugosidade;

    while (passo > 1) { int metade = passo / 2;

        for (int x = metade; x < tamanho; x += passo) {
            for (int y = metade; y < tamanho; y += passo) {
                etapaDiamond(x, y, metade, deslocamento);
            }
        }

        for (int x = 0; x < tamanho; x += metade) {
          
            int inicio = (x % passo == 0) ? metade : 0;
            for (int y = inicio; y < tamanho; y += passo) { etapaSquare(x, y, metade, deslocamento); }
        }
                       
        deslocamento *= 0.5; 
        passo /= 2;
    }
