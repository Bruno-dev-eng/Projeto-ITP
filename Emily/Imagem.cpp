#include "Imagem.h"
#include <fstream>

Imagem::Imagem(int largura, int altura) {
    this->largura = largura;
    this->altura = altura;

    pixels = new Pixel*[this->altura];

    for (int linha = 0; linha < this->altura; linha++) {
        pixels[linha] = new Pixel[this->largura];
    }
}

Imagem::~Imagem() {
    for (int linha = 0; linha < this->altura; linha++) {
        delete[] pixels[linha];
    }

    delete[] pixels;
}

Pixel Imagem::getPixel(int linha, int coluna) {
    return pixels[linha][coluna];
}

void Imagem::setPixel(int linha, int coluna, Pixel cor) {
    pixels[linha][coluna] = cor;
}

void Imagem::lerPPM(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        return;
    }

    std::string formato;
    int novaLargura;
    int novaAltura;
    int maxValor;

    arquivo >> formato;
    arquivo >> novaLargura >> novaAltura;
    arquivo >> maxValor;

    if (novaLargura != largura || novaAltura != altura) {

        for (int linha = 0; linha < altura; linha++) {
            delete[] pixels[linha];
        }

        delete[] pixels;

        largura = novaLargura;
        altura = novaAltura;

        pixels = new Pixel*[altura];

        for (int linha = 0; linha < altura; linha++) {
            pixels[linha] = new Pixel[largura];
        }
    }

    for (int linha = 0; linha < altura; linha++) {
        for (int coluna = 0; coluna < largura; coluna++) {
            int vermelho;
            int verde;
            int azul;

            arquivo >> vermelho >> verde >> azul;

            pixels[linha][coluna] = Cor(vermelho, verde, azul);
        }
    }

    arquivo.close();
}

void Imagem::salvarPPM(const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        return;
    }

    arquivo << "P3\n";
    arquivo << largura << " " << altura << "\n";
    arquivo << "255\n";

    for (int linha = 0; linha < altura; linha++) {
        for (int coluna = 0; coluna < largura; coluna++) {
            arquivo << pixels[linha][coluna].r << " "
                    << pixels[linha][coluna].g << " "
                    << pixels[linha][coluna].b << " ";
        }

        arquivo << "\n";
    }

    arquivo.close();
}